import os
import stat
import pwd
import grp
from os.path import join, getsize

def check(path, is_dir):
    try:
        file_stat = os.stat(path)
    except FileNotFoundError:
        return

    mode = file_stat.st_mode
    mode_u = (mode & stat.S_IRWXU) >> 6
    mode_g = (mode & stat.S_IRWXG) >> 3
    mode_o = (mode & stat.S_IRWXO)
    mode_str = stat.filemode(mode)

    try:
        ownername = pwd.getpwuid(file_stat.st_uid)[0]
    except KeyError:
        ownername = str(file_stat.st_uid)

    try:
        groupname = grp.getgrgid(file_stat.st_gid)[0]
    except KeyError:
        groupname = str(file_stat.st_gid)

    g_neg = ~mode_g & mode_o
    u_neg = (~mode_u & mode_g) | (~mode_u & mode_o)
    if g_neg and u_neg:
        print(f"Negative group+user {mode_str} {ownername:10.10} {groupname:10.10} {path}")
    elif g_neg:
        print(f"Negative group      {mode_str} {ownername:10.10} {groupname:10.10} {path}")
    elif u_neg:
        print(f"Negative user       {mode_str} {ownername:10.10} {groupname:10.10} {path}")

for root, dirs, files in os.walk('.'):
    check(root, True)
    for f in files:
        path = join(root, f)
        check(path, False)
