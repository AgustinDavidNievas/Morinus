import math
import astrology
import chart
import planets
import mtexts
import util


class RiseSet:
	"""Computes Rise/Set times (for the birthday)"""

	RISE, MC, SET, IC = range(0, 4)

	Angles = [astrology.SE_CALC_RISE, astrology.SE_CALC_MTRANSIT , astrology.SE_CALC_SET,  astrology.SE_CALC_ITRANSIT]

	def __init__(self, jd, cal, lon, lat, alt, pls):
		self.jd = jd
		self.cal = cal
		self.lon = lon
		self.lat = lat
		self.alt = alt

		self.calflag = astrology.SE_GREG_CAL
		if self.cal == chart.Time.JULIAN:
			self.calflag = astrology.SE_JUL_CAL

#		self.offs = lon*4.0/1440.0

		self.times = []

		self.calcTimes()

#		self.printRiseSet(pls)


	def calcTimes(self):
		#the date we get from julianday is the same as year, month day in Time-class but we didn't pass it to the init function.
		oyear, omonth, oday, otim = astrology.revjul(self.jd, self.calflag)

		numangles = len(RiseSet.Angles)
		for i in range(planets.Planets.PLANETS_NUM):#Nodes are excluded
			ar = []

			#Rise
			res = astrology.rise_trans(tjdut=self.jd, body=i, flags=astrology.SEFLG_SWIEPH, rsmi=RiseSet.Angles[RiseSet.RISE], geopos=[self.lon, self.lat, self.alt], atpress=0.0, attemp=10.0)
			ret = res[0]
			JDRise = res[1][0]

			tyear, tmonth, tday, ttim = astrology.revjul(JDRise, self.calflag)

			if oyear != tyear or omonth != tmonth or oday != tday:
				res = astrology.rise_trans(tjdut=self.jd-1.0, body=i, flags=astrology.SEFLG_SWIEPH, rsmi=RiseSet.Angles[RiseSet.RISE], geopos=[self.lon, self.lat, self.alt], atpress=0.0, attemp=10.0)
				ret = res[0]
				JDRise = res[1][0]
			#MC
			res = astrology.rise_trans(tjdut=self.jd, body=i, flags=astrology.SEFLG_SWIEPH, rsmi=RiseSet.Angles[RiseSet.MC], geopos=[self.lon, self.lat, self.alt], atpress=0.0, attemp=10.0)
			ret = res[0]
			JDMC = res[1][0]

			tyear, tmonth, tday, ttim = astrology.revjul(JDMC, self.calflag)
			if oyear != tyear or omonth != tmonth or oday != tday:
				res = astrology.rise_trans(tjdut=self.jd-1.0, body=i, flags=astrology.SEFLG_SWIEPH, rsmi=RiseSet.Angles[RiseSet.MC], geopos=[self.lon, self.lat, self.alt], atpress=0.0, attemp=10.0)
				ret = res[0]
				JDMC = res[1][0]

			#Set
			res = astrology.rise_trans(tjdut=self.jd, body=i, flags=astrology.SEFLG_SWIEPH, rsmi=RiseSet.Angles[RiseSet.SET], geopos=[self.lon, self.lat, self.alt], atpress=0.0, attemp=10.0)
			ret = res[0]
			JDSet = res[1][0]

			tyear, tmonth, tday, ttim = astrology.revjul(JDSet, self.calflag)
			if oyear != tyear or omonth != tmonth or oday != tday:
				res = astrology.rise_trans(tjdut=self.jd-1.0, body=i, flags=astrology.SEFLG_SWIEPH, rsmi=RiseSet.Angles[RiseSet.SET], geopos=[self.lon, self.lat, self.alt], atpress=0.0, attemp=10.0)
				ret = res[0]
				JDSet = res[1][0]

			#IC
			res = astrology.rise_trans(tjdut=self.jd, body=i, flags=astrology.SEFLG_SWIEPH, rsmi=RiseSet.Angles[RiseSet.IC], geopos=[self.lon, self.lat, self.alt], atpress=0.0, attemp=10.0)
			ret = res[0]
			JDIC = res[1][0]

			tyear, tmonth, tday, ttim = astrology.revjul(JDIC, self.calflag)
			if oyear != tyear or omonth != tmonth or oday != tday:
				res = astrology.rise_trans(tjdut=self.jd-1.0, body=i, flags=astrology.SEFLG_SWIEPH, rsmi=RiseSet.Angles[RiseSet.IC], geopos=[self.lon, self.lat, self.alt], atpress=0.0, attemp=10.0)
				ret = res[0]
				JDIC = res[1][0]

			#From GMT to Local
#			JDRise += self.offs
			year, month, day, hr = astrology.revjul(JDRise, self.calflag)
			ar.append(hr)

#			JDMC += self.offs
			year, month, day, hr = astrology.revjul(JDMC, self.calflag)
			ar.append(hr)

#			JDSet += self.offs
			year, month, day, hr = astrology.revjul(JDSet, self.calflag)
			ar.append(hr)

#			JDIC += self.offs
			year, month, day, hr = astrology.revjul(JDIC, self.calflag)
			ar.append(hr)

			self.times.append(ar)


	def printRiseSet(self, pls):
		numangles = len(RiseSet.Angles)
		txt = [mtexts.txtsriseset['Rise'], mtexts.txtsriseset['MC'], mtexts.txtsriseset['Set'], mtexts.txtsriseset['IC']]
		print('')
		print('Rise/Set times:')
		for i in range(planets.Planets.PLANETS_NUM):#Nodes are excluded
			for angle in range(numangles):
				h,m,s = util.decToDeg(self.times[i][angle])
				print("%s: %s: %02d:%02d:%02d" % (pls.planets[i].name, txt[angle], h, m, s))
