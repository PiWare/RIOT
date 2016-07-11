#ifndef INTERFACE_DISPLAY_H
#define INTERFACE_DISPLAY_H


namespace interface {

class display
{
	public:
		virtual void set(const bool value) = 0;
		virtual bool get(void) const = 0;

		virtual void draw(const bool value) = 0;
};

}

#endif
