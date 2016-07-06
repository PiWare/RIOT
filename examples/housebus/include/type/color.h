#ifndef TYPE_COLOR_H
#define TYPE_COLOR_H


namespace type {

enum class color:
	std::uint32_t
{
	black		= 0x000000,
	red			= 0x0000FF,
	green		= 0x00FF00,
	blue		= 0xFF0000,
	yellow		= 0x00FFFF,
	cyan		= 0xFFFF00,
	mangenta	= 0xFF00FF,
	white		= 0xFFFFFF,
};

}

#endif
