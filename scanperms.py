'''Check for negative group and user permissions in a filesystem'''

### Copyright 2022 Steven Murdoch
###
### Licensed under the Apache License, Version 2.0 (the "License");
### you may not use this file except in compliance with the License.
### You may obtain a copy of the License at
###
###     http://www.apache.org/licenses/LICENSE-2.0
###
### Unless required by applicable law or agreed to in writing, software
### distributed under the License is distributed on an "AS IS" BASIS,
### WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
### See the License for the specific language governing permissions and
### limitations under the License.

import argparse
import logging
import os
import os.path
import stat
import pwd
import grp
import sys

def check(path: str, show_userneg: bool) -> None:
    '''Check if PATH has negative group permissions and print results.
    If SHOW_USERNEG is true, also show negative user permissions.'''
    try:
        file_stat = os.stat(path)
    except FileNotFoundError:
        ## Could not follow the symlink
        logging.warning("Not found, skipping file: %s", path)
        return
    except PermissionError:
        ## Could not stat file
        logging.warning("Permission denied, skipping file: %s", path)
        return

    ## Extract permission bits for user, group and other
    mode = file_stat.st_mode
    mode_u = (mode & stat.S_IRWXU) >> 6
    mode_g = (mode & stat.S_IRWXG) >> 3
    mode_o = (mode & stat.S_IRWXO)
    mode_str = stat.filemode(mode)

    ## Get names for user and group, if possible
    try:
        ownername = pwd.getpwuid(file_stat.st_uid)[0]
    except KeyError:
        ownername = str(file_stat.st_uid)

    try:
        groupname = grp.getgrgid(file_stat.st_gid)[0]
    except KeyError:
        groupname = str(file_stat.st_gid)

    ## Which bit are set in other but unset in group
    g_neg = ~mode_g & mode_o
    ## Which bits are set in either other or group, but unset in user
    u_neg = ~mode_u & (mode_o | mode_g)

    logging.debug("Checking %s with mode %s (user %s, group %s) - "
        "extra user perms %03o, extra group perms %03o",
        path, mode_str, ownername, groupname, u_neg, g_neg)

    ## If we don't need to know about negative user permissions, clear these
    if not show_userneg:
        u_neg = False

    ## Output the details for the negative permissions found
    if g_neg and u_neg:
        print(f"Negative group+user {mode_str} {ownername:10.10} {groupname:10.10} {path}")
    elif g_neg:
        print(f"Negative group      {mode_str} {ownername:10.10} {groupname:10.10} {path}")
    elif u_neg:
        print(f"Negative user       {mode_str} {ownername:10.10} {groupname:10.10} {path}")

def main() -> None:
    '''Check recursively for negative group/user permissions in a specified directory'''

    ## Parse command line arguments
    parser = argparse.ArgumentParser(
        description="Recursively scan a directory for paths for which dropping group "
            "membership will escalate privilege")
    parser.add_argument('-v', '--verbose', action='store_true',
        help='show debugging output')
    parser.add_argument('-u', '--user', action='store_true',
        help='also show negative user permissions')
    parser.add_argument('dir',
        help='directory to recursively scan')

    arguments = parser.parse_args()

    ## Set up logging handler
    if arguments.verbose:
        logging.basicConfig(format='%(levelname)s:%(message)s', 
            stream=sys.stderr, level=logging.DEBUG)
    else:
        logging.basicConfig(format='%(levelname)s:%(message)s',
            stream=sys.stderr, level=logging.WARN)

    ## Start the scan
    logging.debug("Starting scan at directory %s", arguments.dir)
    for root, _, files in os.walk(arguments.dir):
        ## Check the directory
        check(root, arguments.user)
        for scan_file in files:
            ## Check the files in the directory
            scan_path = os.path.join(root, scan_file)
            check(scan_path, arguments.user)
            ## We don't need to check subdirectories because these will be
            ## checked when they are the root of further iterations

if __name__ == "__main__":
    main()
