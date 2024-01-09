import wx
import profectionswnd
import mrclasses


class ProfsTableFrame(mrclasses.MrSecondFrame):
	def __init__(self, parent, title, pchrts, opts, mainsigs):
		super(ProfsTableFrame, self).__init__(parent, -1, title,
											wx.DefaultPosition,
											wx.Size(640, 400))

		self.parent = parent
		self.mainsigs = mainsigs
		self.sw = profectionswnd.ProfectionsWnd(self, 0, pchrts, opts, parent, mainsigs)

		self.SetMinSize((200, 200))

	def change(self, age, pcharts, opts):
		self.sw.Destroy()
		self.sw = profectionswnd.ProfectionsWnd(self, age, pcharts, opts, self.parent,
												self.mainsigs, -1, self.GetClientSize())
#		if wx.Platform == '__WXMSW__':
#			self.sw.Refresh()
