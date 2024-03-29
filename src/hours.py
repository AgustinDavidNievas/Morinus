import astrology
import util


class PlanetaryHours:
	#From sunrise!! (till next sunrise)
	#Monday: Moon, Saturnus, Jupiter, Mars, Sun, Venus, Mercury, Moon...
	#Sunday: Sun, Venus, Mercury, Moon, Saturnus, Jupiter, Mars, Sun...
	PHs = ((1, 6, 5, 4, 0, 3, 2, 1, 6, 5, 4, 0, 3, 2, 1, 6, 5, 4, 0, 3, 2, 1, 6, 5),
			(4, 0, 3, 2, 1, 6, 5, 4, 0, 3, 2, 1, 6, 5, 4, 0, 3, 2, 1, 6, 5, 4, 0, 3),
			(2, 1, 6, 5, 4, 0, 3, 2, 1, 6, 5, 4, 0, 3, 2, 1, 6, 5, 4, 0, 3, 2, 1, 6),
			(5, 4, 0, 3, 2, 1, 6, 5, 4, 0, 3, 2, 1, 6, 5, 4, 0, 3, 2, 1, 6, 5, 4, 0),
			(3, 2, 1, 6, 5, 4, 0, 3, 2, 1, 6, 5, 4, 0, 3, 2, 1, 6, 5, 4, 0, 3, 2, 1),
			(6, 5, 4, 0, 3, 2, 1, 6, 5, 4, 0, 3, 2, 1, 6, 5, 4, 0, 3, 2, 1, 6, 5, 4),
			(0, 3, 2, 1, 6, 5, 4, 0, 3, 2, 1, 6, 5, 4, 0, 3, 2, 1, 6, 5, 4, 0, 3, 2))


	def __init__(self, lon, lat, altitude, weekday, jd):
		self.risetime = None
		self.settime = None
		self.hrlen = None
		self.daytime = None

		self.weekday = weekday

		#lon, lat, height, atmpress, celsius
		#in GMT, searches after jd!

		res = astrology.rise_trans(tjdut=jd, body=astrology.SE_SUN, flags=astrology.SEFLG_SWIEPH, rsmi=astrology.SE_CALC_RISE, geopos=[lon, lat, float(altitude)], atpress=0.0, attemp=10.0)
		ret = res[0]
		risetime = res[1][0]

		res = astrology.rise_trans(tjdut=jd, body=astrology.SE_SUN, flags=astrology.SEFLG_SWIEPH, rsmi=astrology.SE_CALC_SET, geopos=[lon, lat, float(altitude)], atpress=0.0, attemp=10.0)
		ret = res[0]
		settime = res[1][0]

		#swe_rise_trans calculates only forward!!
		offs = lon*4.0/1440.0
		hr = 0
		HOURSPERHALFDAY = 12.0
		if risetime > settime: # daytime
			self.daytime = True
#			print 'daytime'#

			res = astrology.rise_trans(tjdut=jd-1.0, body=astrology.SE_SUN, flags=astrology.SEFLG_SWIEPH, rsmi=astrology.SE_CALC_RISE, geopos=[lon, lat, float(altitude)], atpress=0.0, attemp=10.0)
			ret = res[0]
			self.risetime = res[1][0]

			res = astrology.rise_trans(tjdut=jd, body=astrology.SE_SUN, flags=astrology.SEFLG_SWIEPH, rsmi=astrology.SE_CALC_SET, geopos=[lon, lat, float(altitude)], atpress=0.0, attemp=10.0)
			ret = res[0]
			self.settime = res[1][0]

			#From GMT to Local
			self.risetime += offs
			self.settime += offs

#			self.logCalc(settime)#
			self.hrlen = (self.settime-self.risetime)/HOURSPERHALFDAY #hrlen(hour-length) is in days
			for i in range(int(HOURSPERHALFDAY)):
				if jd+offs < self.risetime+self.hrlen*(i+1):
					hr = i
					break
		else:# nighttime
			self.daytime = False
#			print 'nightime'#

			res = astrology.rise_trans(tjdut=jd, body=astrology.SE_SUN, flags=astrology.SEFLG_SWIEPH, rsmi=astrology.SE_CALC_RISE, geopos=[lon, lat, float(altitude)], atpress=0.0, attemp=10.0)
			ret = res[0]
			self.risetime = res[1][0]

			res = astrology.rise_trans(tjdut=jd-1.0, body=astrology.SE_SUN, flags=astrology.SEFLG_SWIEPH, rsmi=astrology.SE_CALC_SET, geopos=[lon, lat, float(altitude)], atpress=0.0, attemp=10.0)
			ret = res[0]
			self.settime = res[1][0]

			#From GMT to Local
			self.risetime += offs
			self.settime += offs

			#Is the local birthtime greater than midnight? If so => decrement day because a planetary day is from sunrise to sunrise
			if jd+offs > int(jd+offs)+0.5:
				self.weekday = util.getPrevDay(self.weekday)

			self.hrlen = (self.risetime-self.settime)/HOURSPERHALFDAY
			for i in range(int(HOURSPERHALFDAY)):
				if jd+offs < self.settime+self.hrlen*(i+1):
					hr = i+int(HOURSPERHALFDAY)
					break

		self.planetaryhour = PlanetaryHours.PHs[self.weekday][hr]#planetary day begins from sunrise(not from 0 hour and Planetary hours are not equal!!)
#		print 'planetary hour is: %d' % self.planetaryhour#


	def revTime(self, tjd):
		jy, jm, jd, jh = astrology.revjul(tjd, 1)
		d, m, s = util.decToDeg(jh)
		return (d, m, s)


	def logCalc(self, tjd):
		#in GMT!
		jy, jm, jd, jh = astrology.revjul(tjd, 1)
		d, m, s = util.decToDeg(jh)
		print('GMT: %d.%d.%d %d:%d:%d' % (jy,jm,jd, d, m, s))
