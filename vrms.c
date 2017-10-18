#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <xbps.h>

const char *RMSAPPROVED[] = {
	"Artistic",
	"Apache-2.0",
	"GPL-1",
	"GPL-2",
	"GPL-3",
	"LGPL-2.1",
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
