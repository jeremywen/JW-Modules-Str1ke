#include "JWModules.hpp"

Plugin *pluginInstance;

void init(rack::Plugin *p)
{
	pluginInstance = p;
	p->addModel(modelD1v1de);
	p->addModel(modelStr1ker);
	p->addModel(modelPres1t);
}
