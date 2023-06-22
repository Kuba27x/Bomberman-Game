#include "stdafx.h"
#include "Gui.h"

gui::Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text,
	unsigned character_size, sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
	sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
	short unsigned id)
{
	buttonState = BTN_IDLE;
	this->id = id;

	shape.setPosition(sf::Vector2f(x, y));
	shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idle_color);
	shape.setOutlineThickness(5.f);
	shape.setOutlineColor(outline_idle_color);
	wasPressedLastFrame = false;

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(
		shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	this->outlineIdleColor = outline_idle_color;
	this->outlineHoverColor = outline_hover_color;
	this->outlineActiveColor = outline_active_color;


}

gui::Button::~Button()
{

}

//Accessors
const bool gui::Button::isPressed() const
{
	if (buttonState == BTN_ACTIVE)
		return true;

	return false;
}

const std::string gui::Button::getText() const
{
	return text.getString();
}

const short unsigned& gui::Button::getId() const
{
	return this->id;
}

void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

void gui::Button::setId(const short unsigned id)
{
	this->id = id;
}

//Functions
void gui::Button::update(const sf::Vector2f& mousePos)
{
	//Update hover , pressed states

	//Idle
	buttonState = BTN_IDLE;

	//Hover
	if (shape.getGlobalBounds().contains(mousePos))
	{
		buttonState = BTN_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (!wasPressedLastFrame)
			{
				buttonState = BTN_ACTIVE;
			}
			wasPressedLastFrame = true;
		}
		else
		{
			wasPressedLastFrame = false;
		}

	}

	switch (buttonState)
	{
	case BTN_IDLE:
		shape.setFillColor(idleColor);
		text.setFillColor(textIdleColor);
		shape.setOutlineColor(this->outlineIdleColor);

		break;

	case BTN_HOVER:
		shape.setFillColor(hoverColor);
		text.setFillColor(textHoverColor);
		shape.setOutlineColor(this->outlineHoverColor);


		break;

	case BTN_ACTIVE:
		shape.setFillColor(activeColor);
		text.setFillColor(textActiveColor);
		shape.setOutlineColor(this->outlineActiveColor);

		break;
	}
}
//Drop Down List

void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(shape);
	target.draw(text);
}

gui::DropDownList::DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned nrOfElements, unsigned default_index)
	: font(font), showList(false), keyTimeMax(1.f), keyTime(0.f)
{
	//unsigned nrOfElements = sizeof(list) / sizeof(std::string);

	activeElement = new gui::Button(x, y, width, height, &this->font, list[default_index], 60,
		sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(25, 25, 25, 50),
		sf::Color(80, 80, 80, 200), sf::Color(160, 160, 160, 200), sf::Color(25, 25, 25, 200),
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(25, 25, 25, 50));

	for (size_t i = 0; i < nrOfElements; i++)
	{
		this->list.push_back(new gui::Button(x, y + ((i + 1) * height), width, height, &this->font, list[i], 60,
			sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(25, 25, 25, 50),
			sf::Color(80, 80, 80, 200), sf::Color(160, 160, 160, 200), sf::Color(25, 25, 25, 200),
			sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(25, 25, 25, 0), i));
	}
}

gui::DropDownList::~DropDownList()
{
	delete activeElement;
	for (size_t i = 0; i < this->list.size(); i++)
	{
		delete this->list[i];
	}
}

const unsigned short& gui::DropDownList::getActiveElementId() const
{
	return this->activeElement->getId();
}

const bool gui::DropDownList::getKeyTime()
{
	if (keyTime >= keyTimeMax)
	{
		keyTime = 0.f;
		return true;
	}
	return false;
}

void gui::DropDownList::updateKeyTime(const float& dt)
{
	if (keyTime < keyTimeMax)
		keyTime += 10.f * dt;
}

void gui::DropDownList::update(const sf::Vector2f& mousePos, const float& dt)
{
	updateKeyTime(dt);
	activeElement->update(mousePos);


	//Show, hide list
	if (activeElement->isPressed() && getKeyTime())
	{
		if (showList)
			showList = false;
		else
			showList = true;
	}

	if (showList)
	{
		for (auto& i : this->list)
		{
			i->update(mousePos);

			if (i->isPressed() && getKeyTime())
			{
				showList = false;
				activeElement->setText(i->getText());
				activeElement->setId(i->getId());
			}
		}
	}
}

void gui::DropDownList::render(sf::RenderTarget& target)
{
	activeElement->render(target);
	if (showList)
	{
		for (auto& i : this->list)
		{
			i->render(target);
		}
	}
}

//TextField

gui::TextField::TextField(float x, float y, float width, float height, sf::Font* font, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
	: textFieldState(BTN_IDLE), active(false)
{
	shape.setPosition(sf::Vector2f(x, y));
	shape.setSize(sf::Vector2f(width, height));
	shape.setFillColor(idleColor);
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(sf::Color::White);

	this->font = font;
	text.setFont(*this->font);
	text.setPosition(shape.getPosition().x + 5.f, shape.getPosition().y + 5.f);
	text.setCharacterSize(static_cast<unsigned>(height) - 10);
	text.setFillColor(sf::Color::Black);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;
}

gui::TextField::~TextField()
{
	//...
}

//Accessors
const bool gui::TextField::isActive() const
{
	return active;
}

const std::string gui::TextField::getText() const
{
	return text.getString();
}

//Modifiers
void gui::TextField::setActive(bool active)
{
	this->active = active;
}

//Functions
void gui::TextField::addCharacter(const char character)
{
	// Only accept digits and the dot
	if (isdigit(character) || character == '.')
	{
		sf::String str = text.getString();
		str += character;
		text.setString(str);
	}
}

void gui::TextField::removeCharacter()
{
	sf::String str = text.getString();
	str = str.substring(0, str.getSize() - 1);
	text.setString(str);
}

void gui::TextField::update(const sf::Vector2f& mousePos)
{
	//Idle state
	textFieldState = BTN_IDLE;

	//Hover state
	if (shape.getGlobalBounds().contains(mousePos))
	{
		textFieldState = BTN_HOVER;

		//Pressed state
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			textFieldState = BTN_ACTIVE;
			setActive(true);
		}
	}
	else if (active && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		setActive(false);
	}

	//Change color based on state
	switch (textFieldState)
	{
	case BTN_IDLE:
		shape.setFillColor(idleColor);
		break;

	case BTN_HOVER:
		shape.setFillColor(hoverColor);
		break;

	case BTN_ACTIVE:
		shape.setFillColor(activeColor);
		break;

	default:
		shape.setFillColor(sf::Color::Red); //Error color
		break;
	}
}



void gui::TextField::render(sf::RenderTarget& target)
{
	target.draw(shape);
	target.draw(text);
}