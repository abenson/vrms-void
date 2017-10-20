/*  vrms-void - Implementation of Virtual RMS for Void Linux / XBPS
 *
 *  Copyright (C) 2017 Andrew Benson
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <xbps.h>

const char *RMSAPPROVED[] = {
	"Artistic",
	"Apache-2.0",
	"GPL",
	"LGPL",
	"MIT",
	"BSD",
	"MPL-2.0",
	"Public Domain",
	"zlib",
	"Vim",
	"ISC",
	"PSF",
	"PIL",
	"OFL",
	"tcl/tk",
	"libpng",
	"Boost",
	"Free for any use",
	"CC",
	"ICU",
	"JasPer-2.0",
	"ImageMagick",
	"OSGPL",
	"SCOWL",
	NULL
};

const char *RMSDISAPPROVED[] = {
	"Apache-1.1",
	"Apache-1.0",
	"APSL-2"
	"AGPL-1",
	"BitTorrentOSL-1.1",
	"CeCill",
	"CDDL",
	"CPAL",
	"CPL",
	"Condor",
	"EPL",
	"Gnuplot",
	"IBM",
	"JabberOSL",
	"LPPL",
	"LucentPL",
	"MS-PL",
	"MS-RL",
	"MPL-1.1",
	"NOSL",
	"NokOS",
	"OpenLDAP-2.3",
	"OSL",
	"OpenSSL",
	"Phorum",
	"PHP",
	"PSF-2.0",
	"PSF-2.1",
	"QPL-1.0",
	"RPSL",
	"SISL",
	"SunPL",
	"Xinetd",
	"YPL",
	"Zend",
	"Zimbra",
	"Zope-1.0",
	NULL
};

int test_package(struct xbps_handle *xhp, xbps_object_t obj, const char *key, void *arg, bool *loop_done)
{
	const char *license;
	int approvals = 0;
	int disapprovals = 0;
	int i = 0;

	xbps_dictionary_get_cstring_nocopy(obj, "license", &license);

	i=0;
	while(RMSAPPROVED[i]) {
		if(strcasestr(license, RMSAPPROVED[i]) != NULL) {
			approvals++;
		}
		i++;
	}

	i=0;
	while(RMSDISAPPROVED[i]) {
		if(strcasestr(license, RMSDISAPPROVED[i]) != NULL) {
			printf("%s: %s\n", key, RMSDISAPPROVED[i]);
			return 0;
		}
		i++;
	}

	if(approvals == 0) {
		printf("%s: %s\n", key, license);
	}

	return 0;
}

int main(int argc, char *argv[])
{
	struct xbps_handle xh;

	memset(&xh, 0, sizeof xh);

	if(xbps_init(&xh) != 0) {
		printf("Couldn't initialize package database.\n");
		return 1;
	}

	xbps_pkgdb_foreach_cb(&xh, test_package, NULL);

	xbps_end(&xh);

	return 0;
}
