"""
Downloads and organizes resources needed to play free doom
"""

import argparse
from pathlib import Path
from zipfile import ZipFile
from urllib.request import urlretrieve

GZDOOM_URL = "https://github.com/ZDoom/gzdoom/releases/download/g4.14.2/gzdoom-4-14-2-windows.zip"
FREEDOOM_URL = "https://github.com/freedoom/freedoom/releases/download/v0.13.0/freedoom-0.13.0.zip"

GZDOOM_LICENSE_URL = "https://github.com/ZDoom/gzdoom/blob/master/LICENSE"
FREEDOOM_LICENSE_URL = "https://github.com/freedoom/freedoom/blob/master/COPYING.adoc"


def prompt_user_license_agreement() -> bool:
    prompt = f"""
    === READ CLOSELY!!! ===
    This script downloads,
    - The windows build of GZDOOM from {GZDOOM_URL}
    - WADs (doom resource file) from Freedoom {FREEDOOM_URL}

    Review licenses for GZDOOM {GZDOOM_LICENSE_URL} and Freedoom {FREEDOOM_LICENSE_URL} before continuing.
    """

    prompt_gzdoom = f"""
    {GZDOOM_LICENSE_URL}
    Do you consent to the GZDOOM license? [Y/n]
    """

    prompt_freedoom = f"""
    {FREEDOOM_LICENSE_URL}
    Do you consent to the Freedoom license? [Y/n]
    """

    print(prompt)
    query_usr = lambda l: input(l).strip().lower() == "y"
    return query_usr(prompt_gzdoom) and query_usr(prompt_freedoom)


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

    # check license agreement
    if not prompt_user_license_agreement():
        print("Failed to agree with licenses, exiting...")
        exit(1)

    outdir = args.outdir / "gzdoom"
    outdir.mkdir(parents=True, exist_ok=True)
    download_gzdoom_and_freedoom(outdir)
