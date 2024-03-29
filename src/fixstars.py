import astrology

class FixStars:
	"""Calculates the positions of the fixstars"""

	NAME = 0
	NOMNAME = 1
	LON = 2
	LAT = 3
	RA = 4
	DECL = 5

	def __init__(self, tjd_ut, flag, names, obl):

		self.data = []

		i = 0
		for k in names:
			self.data.append(['', '', 0.0, 0.0, 0.0, 0.0])
			r = astrology.fixstar_ut(','+k, tjd_ut, flag)
			ret = r[2]
			name = r[1]
			dat = r[0]

			nam = name.strip()
			nomnam = ''
			DELIMITER = ','
			if nam.find(DELIMITER) != -1:
				snam = nam.split(DELIMITER)
				nam = snam[0].strip()
				nomnam = snam[1].strip()

			self.data[i][FixStars.NAME] = nam
			self.data[i][FixStars.NOMNAME] = nomnam
			self.data[i][FixStars.LON] = dat[0]
			self.data[i][FixStars.LAT] = dat[1]
			r = astrology.cotrans((dat[0], dat[1], 1.0), -obl)
			ra = r[0]#TODO abajo usa los indices, agregar ceros o modificar abajo en sort?
			decl = r[1]
			dist = r[2]
			self.data[i][FixStars.RA] = ra
			self.data[i][FixStars.DECL] = decl

			i += 1

		self.sort()


	def sort(self):
		num = len(self.data)
		self.mixed = []

		for i in range(num):
			self.mixed.append(i)

		for i in range(num):
			for j in range(num-1):
				if (self.data[j][FixStars.LON] > self.data[j+1][FixStars.LON]):
					tmp = self.data[j][:]
					self.data[j] = self.data[j+1][:]
					self.data[j+1] = tmp[:]
					tmp = self.mixed[j]
					self.mixed[j] = self.mixed[j+1]
					self.mixed[j+1] = tmp
