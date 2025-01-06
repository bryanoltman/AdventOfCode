import argparse
import os
import requests


def download_input(day: int, year: int, session: str, out_dir: str) -> None:
    """Download the input file for a given day and year."""
    day_str = f"{day}".rjust(2, "0")
    filename = f"{day_str}.txt"
    os.makedirs(out_dir, exist_ok=True)
    r = requests.get(
        f"https://adventofcode.com/{year}/day/{day}/input",
        cookies={"session": session},
    )
    with open(f"{out_dir}/{filename}", "w") as f:
        f.write(r.text)


def main():
    """Download input files for each day."""
    parser = argparse.ArgumentParser(description="Download input files for each day.")
    parser.add_argument(
        "--day",
        type=int,
        help="The day for which to download the input file. If not provided, all days will be downloaded.",
    )
    parser.add_argument(
        "--year", type=int, help="The year for which to download the input file."
    )
    parser.add_argument(
        "--session",
        type=str,
        help="The session cookie value from your browser.",
    )
    parser.add_argument(
        "--out",
        type=str,
        help="The output directory in which to save the input files.",
    )
    args = parser.parse_args()
    days = args.day if args.day else range(1, 26)
    out_dir = args.out
    for day in days:
        download_input(day, args.year, args.session, out_dir)


if __name__ == "__main__":
    main()
