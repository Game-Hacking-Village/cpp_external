"""
Downloads and organizes resources needed to play free doom
"""

import argparse
from zipfile import ZipFile
from urllib.request import urlretrieve
from pathlib import Path

GZDOOM_URL = "https://github.com/ZDoom/gzdoom/releases/download/g4.14.2/gzdoom-4-14-2-windows.zip"
FREEDOOM_URL = "https://github.com/freedoom/freedoom/releases/download/v0.13.0/freedoom-0.13.0.zip"


def download_gzdoom_and_freedoom(outpath: Path) -> None:
    print("Downloading gzdoom...")
    gzdoom_zip, _ = urlretrieve(GZDOOM_URL, outpath / "gzdoom.zip")

    print("Downloading freedoom...")
    freedoom_zip, _ = urlretrieve(FREEDOOM_URL, outpath / "freedoom.zip")

    print("Extracting files...")
    # extract gzdoom
    with ZipFile(gzdoom_zip) as zf:
        zf.extractall(outpath)

    # extract wads from freedoom to root gzdoom dir
    with ZipFile(freedoom_zip) as zf:
        for zfile in (z for z in zf.infolist() if z.filename.endswith(".wad")):
            zfile.filename = Path(zfile.filename).name
            zf.extract(zfile, outpath)

    gzdoom_zip.unlink()
    freedoom_zip.unlink()

    print("Done!")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("outdir", help="output dir to download resources to", type=Path)
    args = parser.parse_args()

    outdir = args.outdir / "gzdoom"
    outdir.mkdir(parents=True, exist_ok=True)
    download_gzdoom_and_freedoom(outdir)
