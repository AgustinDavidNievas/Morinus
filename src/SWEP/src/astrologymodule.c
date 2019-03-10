#include <Python.h>
#include "swephexp.h"


/**************************** 
 * exports from sweph.c 
 ****************************/

static PyObject* astrology_swe_version(PyObject *self, PyObject *args)
{
	char sver[256];

	char *pver = swe_version(sver);

	return Py_BuildValue("s", pver);
}

/* planets, moon, nodes etc. */
static PyObject* astrology_swe_calc(PyObject *self, PyObject *args)
{
	double tjd;
	int ipl;
	int iflag;

	if (!PyArg_ParseTuple(args, "dii", &tjd, &ipl, &iflag))
		return NULL;

	double xx[6];
	char serr[AS_MAXCH];
	int ret = swe_calc(tjd, ipl, iflag, xx, serr);

	return Py_BuildValue("(l)(dddddd)(s)", ret, xx[0], xx[1], xx[2], xx[3], xx[4], xx[5], serr);
}
/*int32 swe_calc(double tjd, int ipl, int32 iflag, double *xx, char *serr);*/

static PyObject* astrology_swe_calc_ut(PyObject *self, PyObject *args)
{
	double tjd_ut;
	int ipl;
	int iflag;

	if (!PyArg_ParseTuple(args, "dii", &tjd_ut, &ipl, &iflag))
		return NULL;

	double xx[6];
	char serr[AS_MAXCH];
	int ret = swe_calc_ut(tjd_ut, ipl, iflag, xx, serr);

	return Py_BuildValue("(l)(dddddd)(s)", ret, xx[0], xx[1], xx[2], xx[3], xx[4], xx[5], serr);
}
/*int32 swe_calc_ut(double tjd_ut, int32 ipl, int32 iflag, double *xx, char *serr);*/

/* fixed stars */
static PyObject* astrology_swe_fixstar(PyObject *self, PyObject *args)
{
	char* star;
	double tjd;
	int iflag;

	if (!PyArg_ParseTuple(args, "sdi", &star, &tjd, &iflag))
		return NULL;

	double xx[6];
	char serr[AS_MAXCH];
	int ret = swe_fixstar(star, tjd, iflag, xx, serr);

	return Py_BuildValue("(l)(dddddd)(s)", ret, xx[0], xx[1], xx[2], xx[3], xx[4], xx[5], serr);
}
/*int32 swe_fixstar(char *star, double tjd, int32 iflag, double *xx, char *serr);*/

static PyObject* astrology_swe_fixstar_ut(PyObject *self, PyObject *args)
{
	char* star;
	double tjd_ut;
	int iflag;

	if (!PyArg_ParseTuple(args, "sdi", &star, &tjd_ut, &iflag))
		return NULL;

	char st[64];
  	strncpy(st, star, 63);

	double xx[6];
	char serr[AS_MAXCH];
	int ret = swe_fixstar_ut(&st[0], tjd_ut, iflag, xx, serr);

	return Py_BuildValue("(l)(s)(dddddd)(s)", ret, st, xx[0], xx[1], xx[2], xx[3], xx[4], xx[5], serr);
}
/*ext_def(int32) swe_fixstar_ut(char *star, double tjd_ut, int32 iflag, 
	double *xx, char *serr);*/

static PyObject* astrology_swe_fixstar_mag(PyObject *self, PyObject *args)
{
	char* star;

	if (!PyArg_ParseTuple(args, "s", &star))
		return NULL;

	char st[64];
  	strncpy(st, star, 63);
	double mag;
	char serr[AS_MAXCH];

	int ret = swe_fixstar_mag(st, &mag, serr);

	return Py_BuildValue("(l)(s)(d)(s)", ret, st, mag, serr);
}
/*ext_def(int32) swe_fixstar_mag(char *star, double *mag, char *serr);*/

/* close Swiss Ephemeris */
static PyObject* astrology_swe_close(PyObject *self, PyObject *args)
{
	swe_close();

	Py_INCREF(Py_None);
	return Py_None;
}
/*ext_def( void ) swe_close(void);*/

/* set directory path of ephemeris files */
static PyObject* astrology_swe_set_ephe_path(PyObject *self, PyObject *args)
{
	char* path;

	if (!PyArg_ParseTuple(args, "s", &path))
		return NULL;

	swe_set_ephe_path(path);

	Py_INCREF(Py_None);
	return Py_None;
}
/*ext_def( void ) swe_set_ephe_path(char *path);*/

/* set file name of JPL file */
static PyObject* astrology_swe_set_jpl_file(PyObject *self, PyObject *args)
{
	char* fname;

	if (!PyArg_ParseTuple(args, "s", &fname))
		return NULL;

	swe_set_jpl_file(fname);

	Py_INCREF(Py_None);
	return Py_None;
}
/*ext_def( void ) swe_set_jpl_file(char *fname);*/

/* get planet name */
static PyObject* astrology_swe_get_planet_name(PyObject *self, PyObject *args)
{
	int ipl;
//	char* spname;
	char spname[32];

//	if (!PyArg_ParseTuple(args, "is", &ipl, &spname))
	if (!PyArg_ParseTuple(args, "i", &ipl))
		return NULL;

//	char* str = swe_get_planet_name(ipl, spname);
	char* str = swe_get_planet_name(ipl, &spname[0]);

	return Py_BuildValue("s", str);
}
/*ext_def( char *) swe_get_planet_name(int ipl, char *spname);*/

/* set geographic position of observer */
static PyObject* astrology_swe_set_topo(PyObject *self, PyObject *args)
{
	double geolon, geolat, geoalt;

	if (!PyArg_ParseTuple(args, "ddd", &geolon, &geolat, &geoalt))
		return NULL;

	swe_set_topo(geolon, geolat, geoalt);

	Py_INCREF(Py_None);
	return Py_None;
}
/*ext_def (void) swe_set_topo(double geolon, double geolat, double geoalt);*/

/* set sidereal mode */
static PyObject* astrology_swe_set_sid_mode(PyObject *self, PyObject *args)
{
	int sid_mode;
	double t0, ayan_t0;

	if (!PyArg_ParseTuple(args, "idd", &sid_mode, &t0, &ayan_t0))
		return NULL;

	swe_set_sid_mode(sid_mode, t0, ayan_t0);

	Py_INCREF(Py_None);
	return Py_None;
}
/*ext_def(void) swe_set_sid_mode(int32 sid_mode, double t0, double ayan_t0);*/

/* get ayanamsa */
static PyObject* astrology_swe_get_ayanamsa(PyObject *self, PyObject *args)
{
	double tjd_et;

	if (!PyArg_ParseTuple(args, "d", &tjd_et))
		return NULL;

	double ret = swe_get_ayanamsa(tjd_et);

	return Py_BuildValue("d", ret);
}
/*ext_def(double) swe_get_ayanamsa(double tjd_et);*/

static PyObject* astrology_swe_get_ayanamsa_ut(PyObject *self, PyObject *args)
{
	double tjd_ut;

	if (!PyArg_ParseTuple(args, "d", &tjd_ut))
		return NULL;

	double ret = swe_get_ayanamsa_ut(tjd_ut);

	return Py_BuildValue("d", ret);
}
/*ext_def(double) swe_get_ayanamsa_ut(double tjd_ut);*/

static PyObject* astrology_swe_get_ayanamsa_name(PyObject *self, PyObject *args)
{
	int isidmode;

	if (!PyArg_ParseTuple(args, "i", &isidmode))
		return NULL;

	char* name = swe_get_ayanamsa_name(isidmode);

	return Py_BuildValue("s", name);
}
/*ext_def( char *) swe_get_ayanamsa_name(int32 isidmode);*/


/**************************** 
 * exports from swehel.c 
 ****************************/

static PyObject* astrology_swe_heliacal_ut(PyObject *self, PyObject *args)
{
	double tjd_start, geopos[3], atm[4], obs[6];
	char *objname;
	int eventtype, helflag;

	if (!PyArg_ParseTuple(args, "ddddddddddddddsii", &tjd_start, &geopos[0], &geopos[1], &geopos[2], &atm[0], &atm[1], &atm[2], &atm[3], &obs[0], &obs[1], &obs[2], &obs[3], &obs[4], &obs[5], &objname, &eventtype, &helflag))
		return NULL;

	double dret[50];
	char serr[AS_MAXCH];
	int ret = swe_heliacal_ut(tjd_start, geopos, atm, obs, objname, eventtype, helflag, dret, serr);

	return Py_BuildValue("(l)(dddddddddddddddddddddddddddddddddddddddddddddddddd)(s)", ret, dret[0], dret[1], dret[2], dret[3], dret[4], dret[5], dret[6], dret[7], dret[8], dret[9], dret[10], dret[11], dret[12], dret[13], dret[14], dret[15], dret[16], dret[17], dret[18], dret[19], dret[20], dret[21], dret[22], dret[23], dret[24], dret[25], dret[26], dret[27], dret[28], dret[29], dret[30], dret[32], dret[32], dret[33], dret[34], dret[35], dret[36], dret[37], dret[38], dret[39], dret[40], dret[41], dret[42], dret[43], dret[44], dret[45], dret[46], dret[47], dret[48], dret[49], serr);
}
/*ext_def(int32) swe_heliacal_ut(double tjdstart_ut, double *geopos, double *datm, double *dobs, char *ObjectName, int32 TypeEvent, int32 iflag, double *dret, char *serr);*/

/**************************** 
 * exports from swedate.c 
 ****************************/

static PyObject* astrology_swe_date_conversion(PyObject *self, PyObject *args)
{
	int y, m, d;
	char c;
	double utime, tjd;

	if (!PyArg_ParseTuple(args, "iiidc", &y, &m, &d, &utime, &c))
		return NULL;

	int ret = swe_date_conversion(y, m, d, utime, c, &tjd);

	return Py_BuildValue("id", ret, tjd);
}
/*ext_def( int ) swe_date_conversion(int y, int m, int d, double utime, char c, double *tjd);*/

static PyObject* astrology_swe_julday(PyObject *self, PyObject *args)
{
	int y, m, d;
	double hour;
	int gregflag;

	if (!PyArg_ParseTuple(args, "iiidi", &y, &m, &d, &hour, &gregflag))
		return NULL;

	double ret = swe_julday(y, m, d, hour, gregflag);

	return Py_BuildValue("d", ret);
}
/*ext_def( double ) swe_julday(int year, int month, int day, double hour, int gregflag);*/

static PyObject* astrology_swe_revjul(PyObject *self, PyObject *args)
{
	double jd;
	int gregflag;

	if (!PyArg_ParseTuple(args, "di", &jd, &gregflag))
		return NULL;

	int jyear, jmon, jday;
	double hour;
	swe_revjul(jd, gregflag, &jyear, &jmon, &jday, &hour);

	return Py_BuildValue("iiid", jyear, jmon, jday, hour);
}
/*ext_def( void ) swe_revjul (double jd, int gregflag, int *jyear, int *jmon, int *jday, double *jut);*/

static PyObject* astrology_swe_utc_to_jd(PyObject *self, PyObject *args)
{
	int y, m, d, h, mi;
	double s;
	int calflag;

	if (!PyArg_ParseTuple(args, "iiiiidi", &y, &m, &d, &h, &mi, &s, &calflag))
		return NULL;

	double dret[2];
	char serr[AS_MAXCH];
	swe_utc_to_jd(y, m, d, h, mi, s, calflag, dret, serr);

	return Py_BuildValue("(dd)(s)", dret[0], dret[1], serr);
}
/*ext_def(int32) swe_utc_to_jd(int32 iyear, int32 imonth, int32 iday, int32 ihour, int32 imin, double dsec, int32 gregflag, double *dret, char *serr);*/

static PyObject* astrology_swe_jdet_to_utc(PyObject *self, PyObject *args)
{
	double tjd_et;
	int calflag;

	if (!PyArg_ParseTuple(args, "di", &tjd_et, &calflag))
		return NULL;

	int y, m, d, h, mi;
	double s;

	swe_jdet_to_utc(tjd_et, calflag, &y, &m, &d, &h, &mi, &s);

	return Py_BuildValue("(iiiiid)", y, m, d, h, mi, s);
}
/*ext_def(void) swe_jdet_to_utc(double tjd_et, int32 gregflag, int32 *iyear, int32 *imonth, int32 *iday, int32 *ihour, int32 *imin, double *dsec);*/

static PyObject* astrology_swe_jdut1_to_utc(PyObject *self, PyObject *args)
{
	double tjd_ut;
	int calflag;

	if (!PyArg_ParseTuple(args, "di", &tjd_ut, &calflag))
		return NULL;

	int y, m, d, h, mi;
	double s;

	swe_jdut1_to_utc(tjd_ut, calflag, &y, &m, &d, &h, &mi, &s);

	return Py_BuildValue("(iiiiid)", y, m, d, h, mi, s);
}
/*ext_def(void) swe_jdut1_to_utc(double tjd_ut, int32 gregflag, int32 *iyear, int32 *imonth, int32 *iday, int32 *ihour, int32 *imin, double *dsec);*/

/**************************** 
 * exports from swehouse.c 
 ****************************/

static PyObject* astrology_swe_houses(PyObject *self, PyObject *args)
{
	double tjd_ut, geolat, geolon;
	int hsys;

	if (!PyArg_ParseTuple(args, "dddi", &tjd_ut, &geolat, &geolon, &hsys))
		return NULL;

	double cusps[13], ascmc[10];
	int ret = swe_houses(tjd_ut, geolat, geolon, hsys, cusps, ascmc);

	return Py_BuildValue("(i)(ddddddddddddd)(dddddddddd)", ret, cusps[0], cusps[1], cusps[2], cusps[3], cusps[4], cusps[5], cusps[6], cusps[7], cusps[8], cusps[9], cusps[10], cusps[11], cusps[12], ascmc[0], ascmc[1], ascmc[2], ascmc[3], ascmc[4], ascmc[5], ascmc[6], ascmc[7], ascmc[8], ascmc[9]);
}
/*ext_def( int ) swe_houses(double tjd_ut, double geolat, double geolon, int hsys, double *cusps, double *ascmc);*/

static PyObject* astrology_swe_houses_ex(PyObject *self, PyObject *args)
{
	double tjd_ut, geolat, geolon;
	int hsys;
	int iflag;

	if (!PyArg_ParseTuple(args, "diddi", &tjd_ut, &iflag, &geolat, &geolon, &hsys))
		return NULL;

	double cusps[13], ascmc[10];
	int ret = swe_houses_ex(tjd_ut, iflag, geolat, geolon, hsys, cusps, ascmc);

	return Py_BuildValue("(i)(ddddddddddddd)(dddddddddd)", ret, cusps[0], cusps[1], cusps[2], cusps[3], cusps[4], cusps[5], cusps[6], cusps[7], cusps[8], cusps[9], cusps[10], cusps[11], cusps[12], ascmc[0], ascmc[1], ascmc[2], ascmc[3], ascmc[4], ascmc[5], ascmc[6], ascmc[7], ascmc[8], ascmc[9]);
}
/*ext_def( int ) swe_houses_ex(double tjd_ut, int32 iflag, double geolat, double geolon, int hsys, double *cusps, double *ascmc);*/

static PyObject* astrology_swe_houses_armc(PyObject *self, PyObject *args)
{
	double armc, geolat, eps;
	int hsys;

	if (!PyArg_ParseTuple(args, "dddi", &armc, &geolat, &eps, &hsys))
		return NULL;

	double cusps[13], ascmc[10];
	int ret = swe_houses_armc(armc, geolat, eps, hsys, cusps, ascmc);

	return Py_BuildValue("(i)(ddddddddddddd)(dddddddddd)", ret, cusps[0], cusps[1], cusps[2], cusps[3], cusps[4], cusps[5], cusps[6], cusps[7], cusps[8], cusps[9], cusps[10], cusps[11], cusps[12], ascmc[0], ascmc[1], ascmc[2], ascmc[3], ascmc[4], ascmc[5], ascmc[6], ascmc[7], ascmc[8], ascmc[9]);
}
/*ext_def( int ) swe_houses_armc(double armc, double geolat, double eps, int hsys, double *cusps, double *ascmc);*/

static PyObject* astrology_swe_house_pos(PyObject *self, PyObject *args)
{
	double armc, geolat, eps, xpin[2];
	int hsys;

	if (!PyArg_ParseTuple(args, "dddidd", &armc, &geolat, &eps, &hsys, &xpin[0], &xpin[1]))
		return NULL;

	char serr[AS_MAXCH];
	double ret = swe_house_pos(armc, geolat, eps, hsys, xpin, serr);

	return Py_BuildValue("ds", ret, serr);
}
/*ext_def(double) swe_house_pos(double armc, double geolat, double eps, int hsys, double *xpin, char *serr);*/

/**************************** 
 * exports from swecl.c 
 ****************************/

static PyObject* astrology_swe_gauquelin_sector(PyObject *self, PyObject *args)
{
	double tjd_ut, geopos[3], atpress, attemp;
	int ipl, iflag, imeth;
	char* starname;

	if (!PyArg_ParseTuple(args, "disiiddddd", &tjd_ut, &ipl, &starname, &iflag, &imeth, &geopos[0], &geopos[1], &geopos[2], &atpress, &attemp))
		return NULL;

	double dgsect;
	char serr[AS_MAXCH];
	double ret = swe_gauquelin_sector(tjd_ut, ipl, starname, iflag, imeth, geopos, atpress, attemp, &dgsect, serr);

	return Py_BuildValue("dds", ret, dgsect, serr);
}
/*ext_def(int32) swe_gauquelin_sector(double t_ut, int32 ipl, char *starname, int32 iflag, int32 imeth, double *geopos, double atpress, double attemp, double *dgsect, char *serr);*/

/* computes geographic location and attributes of solar 
 * eclipse at a given tjd */
static PyObject* astrology_swe_sol_eclipse_where(PyObject *self, PyObject *args)
{
	double tjd_ut;
	int ifl;

	if (!PyArg_ParseTuple(args, "di", &tjd_ut, &ifl))
		return NULL;

	double geopos[2], attr[20];
	char serr[AS_MAXCH];
	int ret = swe_sol_eclipse_where(tjd_ut, ifl, geopos, attr, serr);

	return Py_BuildValue("(l)(dd)(dddddddddddddddddddd)(s)", ret, geopos[0], geopos[1], attr[0], attr[1], attr[2], attr[3], attr[4], attr[5], attr[6], attr[7], attr[8], attr[9], attr[10], attr[11], attr[12], attr[13], attr[14], attr[15], attr[16], attr[17], attr[18], attr[19], serr);
}
/*ext_def (int32) swe_sol_eclipse_where(double tjd, int32 ifl, double *geopos, double *attr, char *serr);*/

static PyObject* astrology_swe_lun_occult_where(PyObject *self, PyObject *args)
{
	double tjd;
	int ipl, ifl;
	char* starname;

	if (!PyArg_ParseTuple(args, "disi", &tjd, &ipl, &starname, &ifl))
		return NULL;

	double geopos[2], attr[20];
	char serr[AS_MAXCH];
	int ret = swe_lun_occult_where(tjd, ipl, starname, ifl, geopos, attr, serr);

	return Py_BuildValue("(l)(dd)(dddddddddddddddddddd)(s)", ret, geopos[0], geopos[1], attr[0], attr[1], attr[2], attr[3], attr[4], attr[5], attr[6], attr[7], attr[8], attr[9], attr[10], attr[11], attr[12], attr[13], attr[14], attr[15], attr[16], attr[17], attr[18], attr[19], serr);
}
/*ext_def (int32) swe_lun_occult_where(double tjd, int32 ipl, char *starname, int32 ifl, double *geopos, double *attr, char *serr);*/

/* computes attributes of a solar eclipse for given tjd, geolon, geolat */
static PyObject* astrology_swe_sol_eclipse_how(PyObject *self, PyObject *args)
{
	double tjd, geopos[3];
	int ifl;

	if (!PyArg_ParseTuple(args, "diddd", &tjd, &ifl, &geopos[0], &geopos[1], &geopos[2]))
		return NULL;

	double attr[20];
	char serr[AS_MAXCH];
	int ret = swe_sol_eclipse_how(tjd, ifl, geopos, attr, serr);

	return Py_BuildValue("(l)(dddddddddddddddddddd)(s)", ret, attr[0], attr[1], attr[2], attr[3], attr[4], attr[5], attr[6], attr[7], attr[8], attr[9], attr[10], attr[11], attr[12], attr[13], attr[14], attr[15], attr[16], attr[17], attr[18], attr[19], serr);
}
/*ext_def (int32) swe_sol_eclipse_how(double tjd, int32 ifl, double *geopos, double *attr, char *serr);*/

/* finds time of next local eclipse */
static PyObject* astrology_swe_sol_eclipse_when_loc(PyObject *self, PyObject *args)
{
	double tjd_start, geopos[3];
	int ifl;
	int backward;

	if (!PyArg_ParseTuple(args, "didddi", &tjd_start, &ifl, &geopos[0], &geopos[1], &geopos[2], &backward))
		return NULL;

	double tret[10], attr[20];
	char serr[AS_MAXCH];
	int ret = swe_sol_eclipse_when_loc(tjd_start, ifl, geopos, tret, attr, backward, serr);

	return Py_BuildValue("(l)(dddddddddd)(dddddddddddddddddddd)(s)", ret, tret[0], tret[1], tret[2], tret[3], tret[4], tret[5], tret[6], tret[7], tret[8], tret[9], attr[0], attr[1], attr[2], attr[3], attr[4], attr[5], attr[6], attr[7], attr[8], attr[9], attr[10], attr[11], attr[12], attr[13], attr[14], attr[15], attr[16], attr[17], attr[18], attr[19], serr);
}
/*ext_def (int32) swe_sol_eclipse_when_loc(double tjd_start, int32 ifl, double *geopos, double *tret, double *attr, int32 backward, char *serr);*/

static PyObject* astrology_swe_lun_occult_when_loc(PyObject *self, PyObject *args)
{
	double tjd_start, geopos[3];
	int ifl, ipl;
	char* starname;
	int backward;

	if (!PyArg_ParseTuple(args, "disidddi", &tjd_start, &ipl, &starname, &ifl, &geopos[0], &geopos[1], &geopos[2], &backward))
		return NULL;

	double tret[10], attr[20];
	char serr[AS_MAXCH];
	int ret = swe_lun_occult_when_loc(tjd_start, ipl, starname, ifl, geopos, tret, attr, backward, serr);

	return Py_BuildValue("(l)(dddddddddd)(dddddddddddddddddddd)(s)", ret, tret[0], tret[1], tret[2], tret[3], tret[4], tret[5], tret[6], tret[7], tret[8], tret[9], attr[0], attr[1], attr[2], attr[3], attr[4], attr[5], attr[6], attr[7], attr[8], attr[9], attr[10], attr[11], attr[12], attr[13], attr[14], attr[15], attr[16], attr[17], attr[18], attr[19], serr);
}
/*ext_def (int32) swe_lun_occult_when_loc(double tjd_start, int32 ipl, char *starname, int32 ifl, double *geopos, double *tret, double *attr, int32 backward, char *serr);*/

/* finds time of next eclipse globally */
static PyObject* astrology_swe_sol_eclipse_when_glob(PyObject *self, PyObject *args)
{
	double tjd_start;
	int ifl, ifltype;
	int backward;

	if (!PyArg_ParseTuple(args, "diii", &tjd_start, &ifl, &ifltype, &backward))
		return NULL;

	double tret[10];
	char serr[AS_MAXCH];
	int ret = swe_sol_eclipse_when_glob(tjd_start, ifl, ifltype, tret, backward, serr);

	return Py_BuildValue("(l)(dddddddddddddddddddd)(s)", ret, tret[0], tret[1], tret[2], tret[3], tret[4], tret[5], tret[6], tret[7], tret[8], tret[9], serr);
}
/*ext_def (int32) swe_sol_eclipse_when_glob(double tjd_start, int32 ifl, int32 ifltype, double *tret, int32 backward, char *serr);*/

/* finds time of next occultation globally */
static PyObject* astrology_swe_lun_occult_when_glob(PyObject *self, PyObject *args)
{
	double tjd_start;
	int ipl, ifl, ifltype;
	char* starname;
	int backward;

	if (!PyArg_ParseTuple(args, "didiii", &tjd_start, &ipl, &starname, &ifl, &ifltype, &backward))
		return NULL;

	double tret[10];
	char serr[AS_MAXCH];
	int ret = swe_lun_occult_when_glob(tjd_start, ipl, starname, ifl, ifltype, tret, backward, serr);

	return Py_BuildValue("(l)(dddddddddddddddddddd)(s)", ret, tret[0], tret[1], tret[2], tret[3], tret[4], tret[5], tret[6], tret[7], tret[8], tret[9], serr);
}
/*ext_def (int32) swe_lun_occult_when_glob(double tjd_start, int32 ipl, char *starname, int32 ifl, int32 ifltype, double *tret, int32 backward, char *serr);*/

/* computes attributes of a lunar eclipse for given tjd */
static PyObject* astrology_swe_lun_eclipse_how(PyObject *self, PyObject *args)
{
	double tjd_ut, geopos[3];
	int ifl;

	if (!PyArg_ParseTuple(args, "diddd", &tjd_ut, &ifl, &geopos[0], &geopos[1], &geopos[2]))
		return NULL;

	double attr[20];
	char serr[AS_MAXCH];
	int ret = swe_lun_eclipse_how(tjd_ut, ifl, geopos, attr, serr);

	return Py_BuildValue("(l)(dddddddddddddddddddd)(s)", ret, attr[0], attr[1], attr[2], attr[3], attr[4], attr[5], attr[6], attr[7], attr[8], attr[9], attr[10], attr[11], attr[12], attr[13], attr[14], attr[15], attr[16], attr[17], attr[18], attr[19], serr);
}
/*ext_def (int32) swe_lun_eclipse_how(double tjd_ut, int32 ifl, double *geopos, double *attr, char *serr);*/

static PyObject* astrology_swe_lun_eclipse_when(PyObject *self, PyObject *args)
{
	double tjd_start;
	int ifl, ifltype;
	int backward;

	if (!PyArg_ParseTuple(args, "diii", &tjd_start, &ifl, &ifltype, &backward))
		return NULL;

	double tret[10];
	char serr[AS_MAXCH];
	int ret = swe_lun_eclipse_when(tjd_start, ifl, ifltype, &tret[0], backward, &serr[0]);

	return Py_BuildValue("(l)(dddddddddd)(s)", ret, tret[0], tret[1], tret[2], tret[3], tret[4], tret[5], tret[6], tret[7], tret[8], tret[9], serr);
}
/*ext_def (int32) swe_lun_eclipse_when(double tjd_start, int32 ifl, int32 ifltype, double *tret, int32 backward, char *serr);*/

/* planetary phenomena */
static PyObject* astrology_swe_pheno(PyObject *self, PyObject *args)
{
	double tjd;
	int ipl, iflag;

	if (!PyArg_ParseTuple(args, "dii", &tjd, &ipl, &iflag))
		return NULL;

	double attr[20];
	char serr[AS_MAXCH];
	int ret = swe_pheno(tjd, ipl, iflag, attr, serr);

	return Py_BuildValue("(l)(dddddddddddddddddddd)(s)", ret, attr[0], attr[1], attr[2], attr[3], attr[4], attr[5], attr[6], attr[7], attr[8], attr[9], attr[10], attr[11], attr[12], attr[13], attr[14], attr[15], attr[16], attr[17], attr[18], attr[19], serr);
}
/*ext_def (int32) swe_pheno(double tjd, int32 ipl, int32 iflag, double *attr, char *serr);*/
 
static PyObject* astrology_swe_pheno_ut(PyObject *self, PyObject *args)
{
	double tjd_ut;
	int ipl, iflag;

	if (!PyArg_ParseTuple(args, "dii", &tjd_ut, &ipl, &iflag))
		return NULL;

	double attr[20];
	char serr[AS_MAXCH];
	int ret = swe_pheno_ut(tjd_ut, ipl, iflag, attr, serr);

	return Py_BuildValue("(l)(dddddddddddddddddddd)(s)", ret, attr[0], attr[1], attr[2], attr[3], attr[4], attr[5], attr[6], attr[7], attr[8], attr[9], attr[10], attr[11], attr[12], attr[13], attr[14], attr[15], attr[16], attr[17], attr[18], attr[19], serr);
}
/*ext_def(int32) swe_pheno_ut(double tjd_ut, int32 ipl, int32 iflag, double *attr, char *serr);*/

static PyObject* astrology_swe_refrac(PyObject *self, PyObject *args)
{
	double inalt, atpress, attemp;
	int calc_flag;

	if (!PyArg_ParseTuple(args, "dddi", &inalt, &atpress, &attemp, &calc_flag))
		return NULL;

	int ret = swe_refrac(inalt, atpress, attemp, calc_flag);

	return Py_BuildValue("l", ret);
}
/*ext_def (double) swe_refrac(double inalt, double atpress, double attemp, int32 calc_flag);*/

static PyObject* astrology_swe_refrac_extended(PyObject *self, PyObject *args)
{
	double inalt, geoalt, atpress, lapse_rate, attemp;
	int calc_flag;

	if (!PyArg_ParseTuple(args, "dddddi", &inalt, &geoalt, &atpress, &attemp, &lapse_rate, &calc_flag))
		return NULL;

	double dret[4];
	double ret = swe_refrac_extended(inalt, geoalt, atpress, attemp, lapse_rate, calc_flag, dret);

	return Py_BuildValue("d(dddd)", ret, dret[0], dret[1], dret[2], dret[3]);
}
/*ext_def (double) swe_refrac_extended(double inalt, double geoalt, double atpress, double attemp, double lapse_rate, int32 calc_flag, double *dret);*/

static PyObject* astrology_swe_set_lapse_rate(PyObject *self, PyObject *args)
{
	double lapse_rate;

	if (!PyArg_ParseTuple(args, "d", &lapse_rate))
		return NULL;

	swe_set_lapse_rate(lapse_rate);

	Py_INCREF(Py_None);
	return Py_None;
}
/*ext_def (void) swe_set_lapse_rate(double lapse_rate);*/

static PyObject* astrology_swe_azalt(PyObject *self, PyObject *args)
{
	double tjd_ut, geopos[3], atpress, attemp, xin[3];
	int calc_flag;

	if (!PyArg_ParseTuple(args, "didddddddd", &tjd_ut, &calc_flag, &geopos[0], &geopos[1], &geopos[2], &atpress, &attemp, &xin[0], &xin[1], &xin[2]))
		return NULL;

	double xaz[3];
	swe_azalt(tjd_ut, calc_flag, geopos, atpress, attemp, xin, xaz);

	return Py_BuildValue("ddd", xaz[0], xaz[1], xaz[2]);
}
/*ext_def (void) swe_azalt(double tjd_ut, int32 calc_flag, double *geopos, double atpress, double attemp, double *xin, double *xaz); */

static PyObject* astrology_swe_azalt_rev(PyObject *self, PyObject *args)
{
	double tjd_ut, geopos[3], xin[2];
	int calc_flag;

	if (!PyArg_ParseTuple(args, "diddddd", &tjd_ut, &calc_flag, &geopos[0], &geopos[1], &geopos[2], &xin[0], &xin[1]))
		return NULL;

	double xout[2];
	swe_azalt_rev(tjd_ut, calc_flag, geopos, xin, xout);

	return Py_BuildValue("dd", xout[0], xout[1]);
}
/*ext_def (void) swe_azalt_rev(double tjd_ut, int32 calc_flag, double *geopos, double *xin, double *xout);*/

static PyObject* astrology_swe_rise_trans(PyObject *self, PyObject *args)
{
	double tjd_ut, geopos[3], atpress, attemp;
	int ipl, epheflag, rsmi;
	char* starname;

	if (!PyArg_ParseTuple(args, "disiiddddd", &tjd_ut, &ipl, &starname, &epheflag, &rsmi, &geopos[0], &geopos[1], &geopos[2], &atpress, &attemp))
		return NULL;

	double tret;
	char serr[AS_MAXCH];
	int ret = swe_rise_trans(tjd_ut, ipl, starname, epheflag, rsmi, geopos, atpress, attemp, &tret, serr);

	return Py_BuildValue("lds", ret, tret, serr);
}
/*ext_def (int32) swe_rise_trans(double tjd_ut, int32 ipl, char *starname, int32 epheflag, int32 rsmi, double *geopos, double atpress, double attemp, double *tret, char *serr);*/

static PyObject* astrology_swe_nod_aps(PyObject *self, PyObject *args)
{
	double tjd_et;
	int ipl, iflag, method;

	if (!PyArg_ParseTuple(args, "diii", &tjd_et, &ipl, &iflag, &method))
		return NULL;

	double xnasc[6], xndsc[6], xperi[6], xaphe[6];
	char serr[AS_MAXCH];
	int ret = swe_nod_aps(tjd_et, ipl, iflag, method, xnasc, xndsc, xperi, xaphe, serr);

	return Py_BuildValue("(l)(dddddd)(dddddd)(dddddd)(dddddd)(s)", ret, xnasc[0], xnasc[1], xnasc[2], xnasc[3], xnasc[4], xnasc[5], xndsc[0], xndsc[1], xndsc[2], xndsc[3], xndsc[4], xndsc[5], xperi[0], xperi[1], xperi[2], xperi[3], xperi[4], xperi[5], xaphe[0], xaphe[1], xaphe[2], xaphe[3], xaphe[4], xaphe[5], serr);
}
/*ext_def (int32) swe_nod_aps(double tjd_et, int32 ipl, int32 iflag, int32  method, double *xnasc, double *xndsc, double *xperi, double *xaphe, char *serr);*/

static PyObject* astrology_swe_nod_aps_ut(PyObject *self, PyObject *args)
{
	double tjd_ut;
	int ipl, iflag, method;

	if (!PyArg_ParseTuple(args, "diii", &tjd_ut, &ipl, &iflag, &method))
		return NULL;

	double xnasc[6], xndsc[6], xperi[6], xaphe[6];
	char serr[AS_MAXCH];
	int ret = swe_nod_aps_ut(tjd_ut, ipl, iflag, method, xnasc, xndsc, xperi, xaphe, serr);

	return Py_BuildValue("(l)(dddddd)(dddddd)(dddddd)(dddddd)(s)", ret, xnasc[0], xnasc[1], xnasc[2], xnasc[3], xnasc[4], xnasc[5], xndsc[0], xndsc[1], xndsc[2], xndsc[3], xndsc[4], xndsc[5], xperi[0], xperi[1], xperi[2], xperi[3], xperi[4], xperi[5], xaphe[0], xaphe[1], xaphe[2], xaphe[3], xaphe[4], xaphe[5], serr);
}
/*ext_def (int32) swe_nod_aps_ut(double tjd_ut, int32 ipl, int32 iflag, int32  method, double *xnasc, double *xndsc, double *xperi, double *xaphe, char *serr);*/

/**************************** 
 * exports from swephlib.c 
 ****************************/

/* delta t */
static PyObject* astrology_swe_deltat(PyObject *self, PyObject *args)
{
	double tjd;

	if (!PyArg_ParseTuple(args, "d", &tjd))
		return NULL;

	double ret = swe_deltat(tjd);

	return Py_BuildValue("d", ret);
}
/*ext_def( double ) swe_deltat(double tjd);*/

/* equation of time */
static PyObject* astrology_swe_time_equ(PyObject *self, PyObject *args)
{
	double tjd;

	if (!PyArg_ParseTuple(args, "d", &tjd))
		return NULL;

	double te;
	char serr[AS_MAXCH];
	int ret = swe_time_equ(tjd, &te, serr);

	return Py_BuildValue("ids", ret, te, serr);
}
/*ext_def( int ) swe_time_equ(double tjd, double *te, char *serr);*/

/* sidereal time */
static PyObject* astrology_swe_sidtime0(PyObject *self, PyObject *args)
{
	double tjd_ut, eps, nut;

	if (!PyArg_ParseTuple(args, "ddd", &tjd_ut, &eps, &nut))
		return NULL;

	double ret = swe_sidtime0(tjd_ut, eps, nut);

	return Py_BuildValue("d", ret);
}
/*ext_def( double ) swe_sidtime0(double tjd_ut, double eps, double nut);*/

static PyObject* astrology_swe_sidtime(PyObject *self, PyObject *args)
{
	double tjd_ut;

	if (!PyArg_ParseTuple(args, "d", &tjd_ut))
		return NULL;

	double ret = swe_sidtime(tjd_ut);

	return Py_BuildValue("d", ret);
}
/*ext_def( double ) swe_sidtime(double tjd_ut);*/

/* coordinate transformation polar -> polar */
/* cotrans */
static PyObject* astrology_swe_cotrans(PyObject *self, PyObject *args)
{
	double xpo[3], eps;

	if (!PyArg_ParseTuple(args, "dddd", &xpo[0], &xpo[1], &xpo[2], &eps))
		return NULL;

	double xpn[3];
	swe_cotrans(xpo, xpn, eps);

	return Py_BuildValue("ddd", xpn[0], xpn[1], xpn[2]);
}
/*ext_def( void ) swe_cotrans(double *xpo, double *xpn, double eps);*/

/* swe_cotrans_sp */
static PyObject* astrology_swe_cotrans_sp(PyObject *self, PyObject *args)
{
	double xpo[6], eps;

	if (!PyArg_ParseTuple(args, "ddddddd", &xpo[0], &xpo[1], &xpo[2], &xpo[3], &xpo[4], &xpo[5], &eps))
		return NULL;

	double xpn[6];
	swe_cotrans(xpo, xpn, eps);

	return Py_BuildValue("dddddd", xpn[0], xpn[1], xpn[2], xpn[3], xpn[4], xpn[5]);
}
/*ext_def( void ) swe_cotrans_sp(double *xpo, double *xpn, double eps);*/

/* tidal acceleration to be used in swe_deltat() */
/*ext_def( double ) swe_get_tid_acc(void);*/
/*ext_def( void ) swe_set_tid_acc(double t_acc);*/

/*
ext_def( double ) swe_degnorm(double x);
ext_def( double ) swe_radnorm(double x);
ext_def( double ) swe_rad_midp(double x1, double x0);
ext_def( double ) swe_deg_midp(double x1, double x0);

ext_def( void ) swe_split_deg(double ddeg, int32 roundflag, int32 *ideg, int32 *imin, int32 *isec, double *dsecfr, int32 *isgn);
*/
/******************************************************* 
 * other functions from swephlib.c;
 * they are not needed for Swiss Ephemeris,
 * but may be useful to former Placalc users.
 ********************************************************/

/* normalize argument into interval [0..DEG360] */
/*ext_def( centisec ) swe_csnorm(centisec p);*/

/* distance in centisecs p1 - p2 normalized to [0..360[ */
/*ext_def( centisec ) swe_difcsn (centisec p1, centisec p2);*/

/*ext_def( double ) swe_difdegn (double p1, double p2);*/

/* distance in centisecs p1 - p2 normalized to [-180..180[ */
/*ext_def( centisec ) swe_difcs2n(centisec p1, centisec p2);*/

/*ext_def( double ) swe_difdeg2n(double p1, double p2);*/
/*ext_def( double ) swe_difrad2n(double p1, double p2);*/

/* round second, but at 29.5959 always down */
/*ext_def( centisec ) swe_csroundsec(centisec x);*/

/* double to int32 with rounding, no overflow check */
/*ext_def( int32 ) swe_d2l(double x);*/

/* monday = 0, ... sunday = 6 */
/*ext_def( int ) swe_day_of_week(double jd);*/
/*
ext_def( char *) swe_cs2timestr(CSEC t, int sep, AS_BOOL suppressZero, char *a);

ext_def( char *) swe_cs2lonlatstr(CSEC t, char pchar, char mchar, char *s);

ext_def( char *) swe_cs2degstr(CSEC t, char *a);
*/

static PyMethodDef SWEAstrologyMethods[] = 
{
	{"swe_version", (PyCFunction)astrology_swe_version, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_calc", (PyCFunction)astrology_swe_calc, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_calc_ut", (PyCFunction)astrology_swe_calc_ut, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_fixstar", (PyCFunction)astrology_swe_fixstar, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_fixstar_ut", (PyCFunction)astrology_swe_fixstar_ut, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_fixstar_mag", (PyCFunction)astrology_swe_fixstar_mag, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_set_ephe_path", (PyCFunction)astrology_swe_set_ephe_path, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_close", (PyCFunction)astrology_swe_close, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_set_jpl_file", (PyCFunction)astrology_swe_set_jpl_file, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_get_planet_name", (PyCFunction)astrology_swe_get_planet_name, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_set_topo", (PyCFunction)astrology_swe_set_topo, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_set_sid_mode", (PyCFunction)astrology_swe_set_sid_mode, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_get_ayanamsa", (PyCFunction)astrology_swe_get_ayanamsa, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_get_ayanamsa_ut", (PyCFunction)astrology_swe_get_ayanamsa_ut, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_get_ayanamsa_name", (PyCFunction)astrology_swe_get_ayanamsa_name, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_heliacal_ut", (PyCFunction)astrology_swe_heliacal_ut, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_date_conversion", (PyCFunction)astrology_swe_date_conversion, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_julday", (PyCFunction)astrology_swe_julday, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_revjul", (PyCFunction)astrology_swe_revjul, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_utc_to_jd", (PyCFunction)astrology_swe_utc_to_jd, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_jdet_to_utc", (PyCFunction)astrology_swe_jdet_to_utc, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_jdut1_to_utc", (PyCFunction)astrology_swe_jdut1_to_utc, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_houses", (PyCFunction)astrology_swe_houses, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_houses_ex", (PyCFunction)astrology_swe_houses_ex, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_houses_armc", (PyCFunction)astrology_swe_houses_armc, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_house_pos", (PyCFunction)astrology_swe_house_pos, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_gauquelin_sector", (PyCFunction)astrology_swe_gauquelin_sector, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_sol_eclipse_where", (PyCFunction)astrology_swe_sol_eclipse_where, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_lun_occult_where", (PyCFunction)astrology_swe_lun_occult_where, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_sol_eclipse_how", (PyCFunction)astrology_swe_sol_eclipse_how, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_sol_eclipse_when_loc", (PyCFunction)astrology_swe_sol_eclipse_when_loc, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_lun_occult_when_loc", (PyCFunction)astrology_swe_lun_occult_when_loc, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_sol_eclipse_when_glob", (PyCFunction)astrology_swe_sol_eclipse_when_glob, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_lun_occult_when_glob", (PyCFunction)astrology_swe_lun_occult_when_glob, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_lun_eclipse_how", (PyCFunction)astrology_swe_lun_eclipse_how, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_lun_eclipse_when", (PyCFunction)astrology_swe_lun_eclipse_when, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_pheno", (PyCFunction)astrology_swe_pheno, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_pheno_ut", (PyCFunction)astrology_swe_pheno_ut, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_refrac", (PyCFunction)astrology_swe_refrac, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_refrac_extended", (PyCFunction)astrology_swe_refrac_extended, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_set_lapse_rate", (PyCFunction)astrology_swe_set_lapse_rate, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_azalt", (PyCFunction)astrology_swe_azalt, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_azalt_rev", (PyCFunction)astrology_swe_azalt_rev, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_rise_trans", (PyCFunction)astrology_swe_rise_trans, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_nod_aps", (PyCFunction)astrology_swe_nod_aps, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_nod_aps_ut", (PyCFunction)astrology_swe_nod_aps_ut, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_deltat", (PyCFunction)astrology_swe_deltat, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_time_equ", (PyCFunction)astrology_swe_time_equ, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_sidtime0", (PyCFunction)astrology_swe_sidtime0, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_sidtime", (PyCFunction)astrology_swe_sidtime, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_cotrans", (PyCFunction)astrology_swe_cotrans, METH_VARARGS, "SWEPH.\n"}, 
	{"swe_cotrans_sp", (PyCFunction)astrology_swe_cotrans_sp, METH_VARARGS, "SWEPH.\n"}, 
	{NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC initsweastrology(void)
{
	Py_InitModule("sweastrology", SWEAstrologyMethods);
}



