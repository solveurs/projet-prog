#pragma once
#include "includes.h"
#include "structures.h"

#define NB_PAGE 7
struct AideUI
{
	GtkWidget *texteAide;

};

struct PageInfo{
	GtkWidget *widget;
	int id;
	const gchar *title;
	GtkAssistantPageType type;
};
typedef struct PageInfo PageInfo;
//typedef struct AideImportationUI AideImportationUI;
int uiAide(GtkWidget* widget, gpointer user_data);
void auxAide(GtkWidget* widget, gpointer user_data);
