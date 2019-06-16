#pragma once
#include "rack.hpp"

using namespace rack;
extern Plugin *pluginInstance;

////////////////////////////////////////////// LABELS //////////////////////////////////////////////

struct CenteredLabel : Widget {
	std::string text;
	int fontSize;
	CenteredLabel(int _fontSize = 12) {
		fontSize = _fontSize;
		box.size.y = BND_WIDGET_HEIGHT;
	}
	void draw(const DrawArgs &args) override {
		nvgTextAlign(args.vg, NVG_ALIGN_CENTER);
		nvgFillColor(args.vg, nvgRGB(255, 255, 255));
		nvgFontSize(args.vg, fontSize);
		nvgText(args.vg, box.pos.x, box.pos.y, text.c_str(), NULL);
	}
};

struct SmallWhiteKnob : RoundKnob {
	CenteredLabel* linkedLabel = NULL;
	Module* linkedModule = NULL;

	SmallWhiteKnob() {
		setSVG(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SmallWhiteKnob.svg")));
	}
	
	void connectLabel(CenteredLabel* label, Module* module) {
		linkedLabel = label;
		linkedModule = module;
		if (linkedModule && linkedLabel) {
			linkedLabel->text = formatCurrentValue();
		}
	}

	void onChange(const event::Change &e) override {
		RoundKnob::onChange(e);
		if (linkedModule && linkedLabel) {
			linkedLabel->text = formatCurrentValue();
		}
	}

	virtual std::string formatCurrentValue() {
		if(paramQuantity != NULL){
			return std::to_string(static_cast<unsigned int>(paramQuantity->getValue()));
		}
		return "";
	}
};

struct JwSmallSnapKnob : SmallWhiteKnob {
	JwSmallSnapKnob() {
		snap = true;
	}
};

struct BPMPartKnob : JwSmallSnapKnob {	
	BPMPartKnob(){} 
};

////////////////////////////////////////////// SWITCHES //////////////////////////////////////////////

struct JwHorizontalSwitch : SVGSwitch {
	JwHorizontalSwitch() {
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Switch_Horizontal_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Switch_Horizontal_1.svg")));
	}
};

struct JwVerticalSwitch : SVGSwitch {
	JwVerticalSwitch() {
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Switch_Vertical_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Switch_Vertical_1.svg")));
	}
};

////////////////////////////////////////////// PORTS //////////////////////////////////////////////

struct TinyPJ301MPort : SvgPort {
	TinyPJ301MPort() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/TinyPJ301M.svg")));
	}
};

////////////////////////////////////////////// LIGHTS //////////////////////////////////////////////

struct MyBlueValueLight : ModuleLightWidget {
	MyBlueValueLight() {
		firstLightId = 1;
		addBaseColor(nvgRGB(25, 150, 252));
	}
};

////////////////////////////////////////////// BUTTONS //////////////////////////////////////////////

struct TinyButton : SVGSwitch {
	TinyButton() {
		momentary = true;
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/TinyButtonUp.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/TinyButtonDown.svg")));
	}
};

struct SmallButton : SVGSwitch {
	SmallButton() {
		momentary = true;
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SmallButtonUp.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SmallButtonDown.svg")));
	}
};

////////////////////////////////////////////// SCREWS //////////////////////////////////////////////

struct Screw_J : SVGScrew {
	Screw_J() {
		sw->setSVG(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Screw_J.svg")));
		box.size = sw->box.size;
	}
};

struct Screw_W : SVGScrew {
	Screw_W() {
		sw->setSVG(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Screw_W.svg")));
		box.size = sw->box.size;
	}
};

////////////////////////////////////////////// UTILS //////////////////////////////////////////////

inline int clampijw(int x, int minimum, int maximum) {
	return clamp(x, minimum, maximum);
}
inline float clampfjw(float x, float minimum, float maximum) {
	return fminf(fmaxf(x, minimum), maximum);
}
inline float rescalefjw(float x, float xMin, float xMax, float yMin, float yMax) {
	return yMin + (x - xMin) / (xMax - xMin) * (yMax - yMin);
}

////////////////////////////////////////////// WIDGETS //////////////////////////////////////////////

extern Model *modelStr1ker;
extern Model *modelD1v1de;
extern Model *modelPres1t;

