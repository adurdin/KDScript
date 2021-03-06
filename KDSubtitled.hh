/******************************************************************************
 *  KDSubtitled.hh: *DEPRECATED* HUDSubtitle, KDSubtitled{,AI,VO}
 *
 *  Copyright (C) 2013 Kevin Daughtridge <kevin@kdau.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *****************************************************************************/

#ifndef KDSUBTITLED_HH
#define KDSUBTITLED_HH

#include <Thief/Thief.hh>
using namespace Thief;



class HUDSubtitle : public HUDElement
{
public:
	typedef std::unique_ptr<HUDSubtitle> Ptr;

	HUDSubtitle (const Being& speaker, const SoundSchema& schema,
		const String& text, const Color& color);
	virtual ~HUDSubtitle ();

	SoundSchema get_schema () const { return schema; }

private:
	virtual bool prepare ();
	virtual void redraw ();

	static const ZIndex PRIORITY;
	static const int BORDER, PADDING;
	static const Color BACKGROUND_COLOR;

	Being speaker;
	SoundSchema schema;
	String text;
	Color color;
};



class KDSubtitled : public Script
{
protected:
	KDSubtitled (const String& name, const Object& host);

	virtual void deinitialize ();

	static const float EARSHOT;
	static const Color DEFAULT_COLOR;

	bool start_subtitle (const Being& speaker, const SoundSchema& schema);
	void finish_subtitle (const SoundSchema& schema = Object::ANY);

private:
	Message::Result on_subtitle (Message&);
	Message::Result on_finish_subtitle (TimerMessage&);

	HUDSubtitle::Ptr element;
};



class KDSubtitledAI : public KDSubtitled
{
public:
	KDSubtitledAI (const String& name, const Object& host);

private:
	virtual void initialize ();
	virtual void deinitialize ();
	Message::Result on_property_change (PropertyMessage&);
};



class KDSubtitledVO : public KDSubtitled
{
public:
	KDSubtitledVO (const String& name, const Object& host);

private:
	Message::Result on_turn_on (Message&);
	Message::Result on_initial_delay (TimerMessage&);
};



#endif // KDSUBTITLED_HH

