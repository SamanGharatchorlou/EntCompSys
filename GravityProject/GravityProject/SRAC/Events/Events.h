#pragma once

#include <string>
#include "Utilities/Rect.h"

class Texture;


enum class Event
{
	None,

	SetGameVolume,
	SetMusicVolume,

	UpdateLoadingBar,
	UpdateTextBox,
	SetTextColour,
	SetUIBar,
	SetUISlider,

	Trauma,
	Render,

#if UI_EDITOR
	MoveUIElement,
	ChangeUIElementSize,
#endif
};


struct EventData
{
	EventData() { }
	EventData(Event type) : eventType(type) {}
	virtual ~EventData() { }

	void setEventType(Event event) { eventType = event; }
	Event eventType = Event::None;
};


struct EventPacket
{
	EventPacket(EventData* dataPtr) : data(dataPtr) { }
	~EventPacket() { }

	void free()
	{
		delete data;
		data = nullptr;
	}

	EventData* data;
};


struct RenderEvent : public EventData
{
	RenderEvent(Texture* texture, RectF rect, int renderLayer) : EventData(Event::Render), mTexture(texture), mRect(rect), mRenderLayer(renderLayer) { }

	Texture* mTexture;
	RectF mRect;
	int mRenderLayer;
};


struct SetTextColourEvent : public EventData
{
	SetTextColourEvent(const BasicString& id, SDL_Color colour) : EventData(Event::SetTextColour), mId(id), mColour(colour) { }

	SDL_Color mColour;
	const BasicString mId;
};


struct SetUISlider : public EventData
{
	SetUISlider(const BasicString& id, float value) : EventData(Event::SetUISlider), mId(id), mValue(value) { }

	const BasicString mId;
	float mValue;
};


struct UpdateLoadingBarEvent : public EventData
{
	UpdateLoadingBarEvent() : EventData(Event::UpdateLoadingBar) { }
};


struct SetUIBarEvent : public EventData
{
	SetUIBarEvent(const BasicString bar, const BasicString barContainer, const float percentage) : EventData(Event::SetUIBar),
		mBar(bar), mBarContainer(barContainer), mPercentage(percentage) { }

	const BasicString mBar;
	const BasicString mBarContainer;
	const float mPercentage;
};


struct UpdateTextBoxEvent : public EventData
{
	UpdateTextBoxEvent(const BasicString& id, const BasicString& text) : EventData(Event::UpdateTextBox), mId(id), mText(text) { }

	const BasicString mId;
	const BasicString mText;
};


struct TraumaEvent : public EventData
{
	TraumaEvent(float trauma) : EventData(Event::Trauma), mTrauma(trauma) { }

	const float mTrauma;
};


struct SetVolumeEvent : public EventData
{
	SetVolumeEvent(float volume) : mVolume(volume) { } 

	const float mVolume;
};


#if UI_EDITOR
struct EditUIRectEvent : public EventData
{
	EditUIRectEvent(const BasicString& id, VectorF change) : mId(id), mChange(change) { };
	~EditUIRectEvent() { };

	const BasicString mId;
	const VectorF mChange;
};
#endif