#pragma once

#include <JuceHeader.h>

using namespace juce;

class MyLookAndFeel : public LookAndFeel_V4

    MyLookAndFeel()
    {
        setColour(ComboBox::backgroundColourId, Colours::grey);
        setColour(ComboBox::textColourId, Colours::black);
        setColour(ComboBox::buttonColourId, Colours::darkgrey);
        setColour(ComboBox::outlineColourId, Colours::darkgrey);
        setColour(PopupMenu::backgroundColourId, Colour::fromRGBA(220, 216, 215, 255));
        setColour(PopupMenu::textColourId, Colours::black);
        setColour(PopupMenu::highlightedBackgroundColourId, Colour(160, 160, 160));
        setColour(Label::textColourId, Colour(245, 245, 245));

        setColour(TextButton::buttonColourId, Colours::darkgrey);
        setColour(TextButton::buttonOnColourId, Colours::lightgrey);
        setColour(TextButton::textColourOffId, Colours::darkgrey);
        setColour(TextButton::textColourOnId, Colours::darkgrey);

    }

    ~MyLookAndFeel() override {}

    void drawPopupMenuBackground(Graphics& g, int width, int height) override
    {
        LookAndFeel_V4::drawPopupMenuBackground(g, width, height);

        g.setColour(Colour(5, 5, 5));
        g.drawRect(0, 0, width, height); 
    }

    PopupMenu::Options getOptionsForComboBoxPopupMenu(ComboBox& box, Label& label) override
    {
        PopupMenu::Options option = LookAndFeel_V4::getOptionsForComboBoxPopupMenu(box, label);
        return option.withStandardItemHeight((int)(label.getHeight()));
    };

    void drawButtonText(Graphics& g,
        TextButton& button,
        bool shouldDrawButtonAsHighlighted,
        bool shouldDrawButtonAsDown
    )
    {
        String buttonText = button.getButtonText();

        auto buttonArea = button.getLocalBounds();

        Colour textColour = button.findColour(shouldDrawButtonAsDown ? TextButton::textColourOnId
            : TextButton::textColourOffId)
            .withMultipliedAlpha(button.isEnabled() ? 1.0f : 0.5f);

        g.setColour(textColour);

        if (buttonText == "<")
        {
            Path leftArrow;
            leftArrow.startNewSubPath(buttonArea.getWidth() * 0.7f, buttonArea.getHeight() * 0.2f);
            leftArrow.lineTo(buttonArea.getWidth() * 0.3f, buttonArea.getHeight() * 0.5f);
            leftArrow.lineTo(buttonArea.getWidth() * 0.7f, buttonArea.getHeight() * 0.8f);

            g.strokePath(leftArrow, PathStrokeType(1.0f));
        }
        else if (buttonText == ">") 
        {
            Path rightArrow;
            rightArrow.startNewSubPath(buttonArea.getWidth() * 0.3f, buttonArea.getHeight() * 0.2f);
            rightArrow.lineTo(buttonArea.getWidth() * 0.7f, buttonArea.getHeight() * 0.5f);
            rightArrow.lineTo(buttonArea.getWidth() * 0.3f, buttonArea.getHeight() * 0.8f);

            g.strokePath(rightArrow, PathStrokeType(1.0f));
        }
    }

    void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour, bool isMouseOver, bool isButtonDown) override
    {
        auto buttonArea = button.getLocalBounds();

        Colour buttonColour = button.findColour(TextButton::buttonColourId);

        g.setColour(buttonColour);
        g.fillRect(buttonArea.toFloat());

        if (isMouseOver)
            g.setColour(button.findColour(TextButton::buttonOnColourId).withAlpha(0.5f));
        else
            g.setColour(button.findColour(TextButton::buttonOnColourId));

        g.fillRect(buttonArea.reduced(1));

    }


    void drawComboBox(Graphics& g, int 	width,
        int 	height,
        bool 	isButtonDown,
        int 	buttonX,
        int 	buttonY,
        int 	buttonW,
        int 	buttonH, ComboBox& box) override
    {
        auto outline = box.findColour(ComboBox::outlineColourId);
        g.setColour(outline);
        g.drawRect(0, 0, width, height, 1);
    }

    void positionComboBoxText(juce::ComboBox& comboBox, juce::Label& label) override
    {
        label.setFont(getComboBoxFont(comboBox));
        label.setJustificationType(juce::Justification::centred);
        label.setBounds(1, 1, comboBox.getWidth() - 2, comboBox.getHeight() - 2);
    }

    void drawPopupMenuItem(Graphics& g, const Rectangle<int>& area,
        const bool isSeparator, const bool isActive,
        const bool isHighlighted, const bool isTicked,
        const bool hasSubMenu, const String& text,
        const String& shortcutKeyText,
        const Drawable* icon, const Colour* textColour) override
    {
        if (isHighlighted)
        {
            g.setColour(findColour(PopupMenu::highlightedBackgroundColourId));
            g.fillRect(area);
        }

        g.setColour(findColour(PopupMenu::textColourId));
        g.setFont(getPopupMenuFont());
        g.drawText(text, area, Justification::centred);

        if (isSeparator)
        {
            g.setColour(findColour(PopupMenu::textColourId));
            g.drawLine(area.getX() + 4, area.getCentreY(), area.getRight() - 4, area.getCentreY());
        }

    }

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MyLookAndFeel)
};

