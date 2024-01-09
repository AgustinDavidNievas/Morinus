import math
import astrology
import chart
import util


class Houses:
	"""Calculates the cusps of the Houses"""
	hsys = None
	obl = None
	cusps = None
	ascmc = None
	ascmc2 = None
	regioMPAsc = None
	regioMPMC = None
	cuspstmp = None
	cusps2 = None

	HOUSE_NUM = 12
	hsystems = ('P', 'K', 'R', 'C', 'E', 'W', 'X', 'M', 'H', 'T', 'B', 'O')

	ASC, MC, ARMC, VERTEX, EQUASC, COASC, COASC2, POLARASC = range(0, 8)

	LON = 0
	LAT = 1
	RA = 2
	DECL = 3

	def __init__(self, tjd_ut, flag, geolat, geolon, hsys, obl, ayanopt, ayan):
		if hsys in Houses.hsystems:
			self.hsys = hsys
		else:
			self.hsys = self.hsystems[0]

		self.obl = obl

		#res, self.cusps, self.ascmc = astrology.houses_ex(tjd_ut, flag, geolat, geolon, ord(self.hsys))
		res = astrology.houses_ex(tjdut=tjd_ut, flags=flag, lat=geolat, lon=geolon, hsys=str.encode(self.hsys))
		self.cusps = (0.0,) + res[0] #TODO debugguear todo lugar donde impacta para sacar esta chanchada
		self.ascmc = res[1] + (0.0, 0.0) #TODO debugguear todo lugar donde impacta para sacar esta chanchada
		#TODO self.ascmc aca retorna 8 items en lugar de 10 como antes, pero aparentemente esos ultimos dos son 0.0, asi que si algo falla, agregar dos ceros float en la tupla de esta respuesta...

		##################
		if ayanopt != 0 and self.hsys == 'W':
			del self.cusps
			cusps = [0.0]
			sign = int(util.normalize(self.ascmc[Houses.ASC]-ayan))/30
			cusps.append(sign*30.0)
			for i in range(2, Houses.HOUSE_NUM+1):
				hc = util.normalize(cusps[i-1]+30.0)#TODO ver que onda con el i-1, ahora cusps y ascmc vienen con distinta cantidad de elementos, anteriormente eran ceros
				cusps.append(hc)

			#to tuple (which is a read-only list)
			self.cusps = tuple(cusps)
		##################

		res_asc = astrology.cotrans((self.ascmc[Houses.ASC], 0.0, 1.0), -obl)
		ascra = res_asc[0]
		ascdecl = res_asc[1]
		dist = res_asc[2]

		res_mc = astrology.cotrans((self.ascmc[Houses.MC], 0.0, 1.0), -obl)
		mcra = res_mc[0]
		mcdecl = res_mc[1]
		dist = res_mc[2]

		self.ascmc2 = ((self.ascmc[Houses.ASC], 0.0, ascra, ascdecl), (self.ascmc[Houses.MC], 0.0, mcra, mcdecl))

		#zdAsc=90.0, zdMC=0.0
		#poleAsc=lat, poleMC=0.0
		qasc = math.degrees(math.asin(math.tan(math.radians(ascdecl))*math.tan(math.radians(geolat))))
		self.regioMPAsc = ascra-qasc
		self.regioMPMC = mcra

		self.cuspstmp = [[0.0, 0.0], [0.0, 0.0], [0.0, 0.0], [0.0, 0.0], [0.0, 0.0], [0.0, 0.0], [0.0, 0.0], [0.0, 0.0], [0.0, 0.0], [0.0, 0.0], [0.0, 0.0], [0.0, 0.0]]
		for i in range(Houses.HOUSE_NUM):
			r = astrology.cotrans((self.cusps[i], 0.0, dist), -obl)
			self.cuspstmp[i][0] = r[0]
			self.cuspstmp[i][1] = r[1]
			dist = r[2]

		self.cusps2 = ((self.cuspstmp[0][0], self.cuspstmp[0][1]), (self.cuspstmp[1][0], self.cuspstmp[1][1]), (self.cuspstmp[2][0], self.cuspstmp[2][1]), (self.cuspstmp[3][0], self.cuspstmp[3][1]), (self.cuspstmp[4][0], self.cuspstmp[4][1]), (self.cuspstmp[5][0], self.cuspstmp[5][1]), (self.cuspstmp[6][0], self.cuspstmp[6][1]), (self.cuspstmp[7][0], self.cuspstmp[7][1]), (self.cuspstmp[8][0], self.cuspstmp[8][1]), (self.cuspstmp[9][0], self.cuspstmp[9][1]), (self.cuspstmp[10][0], self.cuspstmp[10][1]), (self.cuspstmp[11][0], self.cuspstmp[11][1]))


	#Zodiacal
	def getHousePos(self, lon, opts, useorbs = False):
		for i in range(1, Houses.HOUSE_NUM):
			orb1 = 0.0
			orb2 = 0.0

			if useorbs:
				orb1 = opts.orbiscuspH
				orb2 = opts.orbiscuspH
				if i == 1 or i == 4 or i == 7 or i == 10:
					orb1 = opts.orbiscuspAscMC
				if i+1 == 4 or i+1 == 7 or i+1 == 10:
					orb2 = opts.orbiscuspAscMC

			cusp1 = util.normalize(self.cusps[i]-orb1)
			cusp2 = util.normalize(self.cusps[i+1]-orb2)#TODO sacar el +1?

			pos = lon
			if cusp1 > 240.0 and cusp2 < 120.0: #Pisces-Aries check
				if pos > 240.0:#planet is in the Pisces-part
					cusp2 += 360.0
				else:
					cusp2 += 360.0
					pos += 360.0

			if cusp1 < pos and cusp2 > pos:
				if opts.traditionalaspects:
					pos = lon
					cusp1 = self.cusps[i]
					cusp2 = self.cusps[i+1]#TODO sacar el +1?
					if cusp1 > 240.0 and cusp1 < 120.0: #Pisces-Aries check
						if pos > 240.0:#planet is in the Pisces-part
							cusp2 += 360.0
						else:
							cusp2 += 360.0
							pos += 360.0

					if cusp1 > pos:
						sign1 = int(lon/chart.Chart.SIGN_DEG)
						sign2 = int(self.cusps[i]/chart.Chart.SIGN_DEG)
						if sign1 != sign2:
							if i == 1:
								return 11
							else:
								return i-2

				return i-1

		#12-I
		orb1 = 0.0
		orb2 = 0.0

		if useorbs:
			orb1 = opts.orbiscuspH
			orb2 = opts.orbiscuspAscMC

		cusp1 = util.normalize(self.cusps[12]-orb1)
		cusp2 = util.normalize(self.cusps[1]-orb2)

		pos = lon
		if cusp1 > 240.0 and cusp2 < 120.0: #Pisces-Aries check
			if pos > 240.0:#planet is in the Pisces-part
				cusp2 += 360.0
			else:
				cusp2 += 360.0
				pos += 360.0

		if cusp1 < pos and cusp2 > pos:
			if opts.traditionalaspects:
				pos = lon
				cusp1 = self.cusps[i]
				cusp2 = self.cusps[i+1]#TODO sacar el +1?
				if cusp1 > 240.0 and cusp1 < 120.0: #Pisces-Aries check
					if pos > 240.0:#planet is in the Pisces-part
						cusp2 += 360.0
					else:
						cusp2 += 360.0
						pos += 360.0

				if cusp1 > pos:
					sign1 = int(lon/chart.Chart.SIGN_DEG)
					sign2 = int(self.cusps[i]/chart.Chart.SIGN_DEG)
					if sign1 != sign2:
						if i == 1:
							return 11
						else:
							return i-2

			return 11

		return 0


	def calcProfPos(self, prof):
		hcs = [self.cusps[0]]
		for i in range(1, Houses.HOUSE_NUM+1):
			hcs.append(util.normalize(self.cusps[i]+prof.offs))

		#to tuple (which is a read-only list)
		self.cusps = tuple(hcs)

		self.ascmc = (util.normalize(self.ascmc[Houses.ASC]+prof.offs), util.normalize(self.ascmc[Houses.MC]+prof.offs), self.ascmc[Houses.ARMC], self.ascmc[Houses.VERTEX], self.ascmc[Houses.EQUASC], self.ascmc[Houses.COASC], self.ascmc[Houses.COASC2], self.ascmc[Houses.POLARASC])

		res_asc = astrology.cotrans((self.ascmc[Houses.ASC], 0.0, 1.0), -self.obl)
		ascra = res_asc[0]
		ascdecl = res_asc[1]
		dist = res_asc[2]

		res_mc = astrology.cotrans((self.ascmc[Houses.MC], 0.0, 1.0), -self.obl)
		mcra = res_mc[0]
		mcdecl = res_mc[1]
		dist = res_mc[2]

		self.ascmc2 = ((self.ascmc[Houses.ASC], 0.0, ascra, ascdecl), (self.ascmc[Houses.MC], 0.0, mcra, mcdecl))
