#!/usr/bin/env python3
"""
safety_budget.py — Track mutation_scanner heuristic counts against configured budgets.

Usage:
    python3 safety_budget.py --ci
    python3 safety_budget.py --update-budget
    python3 safety_budget.py --report
"""

from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path

CODEGEN = Path(__file__).resolve().parent
MUTATIONS = CODEGEN.parent
BUDGET_FILE = MUTATIONS / "config" / "safety_budget.json"

sys.path.insert(0, str(CODEGEN))
from mutation_scanner import group_issues, run_scan  # noqa: E402


def count_categories() -> dict[str, int]:
    result = run_scan(validate_ui=False)
    _, by_category = group_issues(result.issues)
    return {cat: len(items) for cat, items in sorted(by_category.items())}


def load_budget() -> dict:
    if not BUDGET_FILE.exists():
        return {"categories": {}}
    with open(BUDGET_FILE, encoding="utf-8") as f:
        return json.load(f)


def save_budget(data: dict) -> None:
    BUDGET_FILE.parent.mkdir(parents=True, exist_ok=True)
    with open(BUDGET_FILE, "w", encoding="utf-8") as f:
        json.dump(data, f, indent=2)
        f.write("\n")


def update_budget(headroom: float = 1.15) -> dict:
    counts = count_categories()
    budget = load_budget()
    budget["schema_version"] = 1
    budget["headroom_factor"] = headroom
    budget["categories"] = {
        cat: max(int(count * headroom) + 1, count)
        for cat, count in counts.items()
    }
    save_budget(budget)
    return budget


def check_budget() -> tuple[bool, list[str]]:
    counts = count_categories()
    budget = load_budget()
    limits = budget.get("categories", {})
    failures: list[str] = []

    for cat, count in sorted(counts.items()):
        limit = limits.get(cat)
        if limit is None:
            failures.append(f"{cat}: {count} (no budget entry — run --update-budget)")
        elif count > limit:
            failures.append(f"{cat}: {count} > budget {limit}")

    for cat in sorted(set(limits) - set(counts)):
        if limits[cat] == 0 and counts.get(cat, 0) == 0:
            continue

    return len(failures) == 0, failures


def main() -> int:
    parser = argparse.ArgumentParser(description="Mutation safety budget tracker")
    parser.add_argument("--ci", action="store_true", help="Fail if counts exceed budget")
    parser.add_argument("--update-budget", action="store_true", help="Rewrite budget from current counts")
    parser.add_argument("--report", action="store_true", help="Print counts vs budget")
    args = parser.parse_args()

    if args.update_budget:
        existing = load_budget()
        headroom = existing.get("headroom_factor", 1.15)
        budget = update_budget(headroom)
        print(f"Updated {BUDGET_FILE}")
        for cat, limit in sorted(budget["categories"].items()):
            print(f"  {cat}: {limit}")
        return 0

    counts = count_categories()
    limits = load_budget().get("categories", {})

    if args.report or args.ci:
        print("Safety budget report")
        print("=" * 50)
        all_cats = sorted(set(counts) | set(limits))
        for cat in all_cats:
            count = counts.get(cat, 0)
            limit = limits.get(cat, "?")
            status = "OK" if isinstance(limit, int) and count <= limit else "OVER" if isinstance(limit, int) else "?"
            print(f"  [{status}] {cat}: {count} / {limit}")
        print("=" * 50)

    if args.ci:
        ok, failures = check_budget()
        if not ok:
            for msg in failures:
                print(f"FAIL: {msg}")
            return 1
        print("safety_budget --ci: OK")
        return 0

    if not args.report:
        parser.print_help()
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
