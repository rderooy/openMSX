// $Id$

#ifndef __MSXBUNSETSU_HH__
#define __MSXBUNSETSU_HH__

#include "MSXMemDevice.hh"
#include "MSXRomDevice.hh"


class MSXBunsetsu : public MSXMemDevice
{
	public:
		MSXBunsetsu(MSXConfig::Device *config, const EmuTime &time);
		virtual ~MSXBunsetsu();
		
		virtual void reset(const EmuTime &time);
		
		virtual byte readMem(word address, const EmuTime &time);
		virtual void writeMem(word address, byte value, const EmuTime &time);  
		virtual byte* getReadCacheLine(word start);

	private:
		MSXRomDevice rom;
		MSXRomDevice jisyoRom;
		int jisyoAddress;
};
#endif
