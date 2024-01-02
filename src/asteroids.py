import astrology


class Asteroid:
	"""Data of an Asteroid"""

	def __init__(self, tjd_ut, aId, flag):
		self.aId = aId

		r = astrology.calc_ut(tjd_ut, aId, flag)
		rflag = r[1]
		dat = r[0]
		r2 = astrology.calc_ut(tjd_ut, aId, flag+astrology.SEFLG_EQUATORIAL)
		rflag = r2[1]
		datEqu = r2[0]
		self.data = (dat[0], dat[1], datEqu[0], datEqu[1])

		self.name = astrology.get_planet_name(aId)


class Asteroids:
	"""Calculates the positions of the asteroids"""

	ids = [astrology.SE_CERES, astrology.SE_CHIRON, astrology.SE_JUNO, astrology.SE_PALLAS, astrology.SE_PHOLUS, astrology.SE_VESTA]

	def __init__(self, tjd_ut, flag):
		self.asteroids = []

		for i in Asteroids.ids:
			self.asteroids.append(Asteroid(tjd_ut, i, flag))
