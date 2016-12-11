#include <gtk/gtk.h>
#include <stdlib.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <stdio.h>

void zoomin(GtkWidget *pWidget, gpointer data);
void zoomout(GtkWidget *pWidget, gpointer data);
void on_about_btn(GtkWidget *pBtn,gpointer data);

int main(int argc, char **argv)
{
        /*initialiser la gtk*/
        gtk_init(&argc,&argv);

        /*---------------  Variables  ----------------*/
        GtkWidget *pWindow;
        GtkWidget *pVbox, *pHbox;
        GtkWidget *zoom_in, *zoom_out, *Quitter;
        GtkWidget *Image;
        GtkWidget * scroll;
        GtkWidget *Toolbar;
        GtkWidget *zoomicon, *dezoomicon, *exit, *help;
         GdkPixbuf *buf;


        /*-------------------fenetre------------------*/

        pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        //position de la fentre
        gtk_window_set_position(GTK_WINDOW(pWindow),GTK_WIN_POS_CENTER);
        //titre de la fentre
        gtk_window_set_title(GTK_WINDOW(pWindow),"titre temporaire de la fentre");
        //taille de la fenetre  width x height
        gtk_window_set_default_size(GTK_WINDOW(pWindow), 1700,920);
        //signal pour detruire la fentre 
        g_signal_connect(G_OBJECT(pWindow),"destroy",G_CALLBACK(gtk_main_quit),NULL);
       
        
        
        /*----------------   Image   --------------------*/
     //   Image = gtk_image_new_from_file("bourges.jpeg");
        buf = gdk_pixbuf_new_from_file_at_size("map.png",1000,1000,NULL);
        Image = gtk_image_new_from_pixbuf(buf);
        zoomicon = gtk_image_new_from_file("zoom-in.png");
        dezoomicon = gtk_image_new_from_file("zoom-out.png");
        
        help = gtk_image_new_from_file("info.png");
        exit = gtk_image_new_from_file("logout.png");
        /*-------------------   boutton   --------------------*/
        zoom_in = gtk_button_new_with_label("Zoom IN");
        zoom_out = gtk_button_new_with_label("Zoom Out");
        Quitter = gtk_button_new_with_mnemonic("_Quitter");
        g_signal_connect(G_OBJECT(Quitter),"clicked",G_CALLBACK(on_about_btn),(GtkWidget *) pWindow);
        g_signal_connect(G_OBJECT(zoom_in),"clicked",G_CALLBACK(zoomin),Image);
        g_signal_connect(G_OBJECT(zoom_out),"clicked",G_CALLBACK(zoomout),Image);
       
        /*------------ bare d'outil ------------*/

        Toolbar = gtk_toolbar_new();


        /*-------------------------------------------------------*/
        gtk_toolbar_append_item(GTK_TOOLBAR(Toolbar),"HELP","section pour aide",NULL,help,G_CALLBACK(on_about_btn),(GtkWidget*) pWindow);
        gtk_toolbar_append_item(GTK_TOOLBAR(Toolbar),"Zoom in","zoomer la carte",NULL,zoomicon,G_CALLBACK(zoomin),Image);
        gtk_toolbar_append_item(GTK_TOOLBAR(Toolbar),"Zoom out","dezoomer la carte",NULL,dezoomicon,G_CALLBACK(zoomout),Image);
        gtk_toolbar_append_item(GTK_TOOLBAR(Toolbar),"Exit","quitter la fenetre",NULL,exit,G_CALLBACK(gtk_main_quit),NULL);
       gtk_toolbar_append_space(GTK_TOOLBAR(Toolbar));
       
    /*----------------------------------------------------------*/
        /*----------   boite   -----------*/
        pVbox = gtk_vbox_new(FALSE,5);
        gtk_container_add(GTK_CONTAINER(pWindow),pVbox);

        gtk_box_pack_start(GTK_BOX(pVbox),Toolbar,FALSE,FALSE,5);

    //    gtk_box_pack_start(GTK_BOX(pVbox),Image,TRUE,FALSE,0);

        pHbox = gtk_hbox_new(TRUE,5);
        gtk_box_pack_start(GTK_BOX(pVbox),pHbox,FALSE,FALSE,5);

        gtk_box_pack_start(GTK_BOX(pHbox),zoom_in,TRUE,TRUE,0);
        gtk_box_pack_start(GTK_BOX(pHbox),zoom_out,TRUE,TRUE,0);
        gtk_box_pack_start(GTK_BOX(pHbox),Quitter,TRUE,TRUE,0);


        /*--------------barre de defilment ----------------*/
        scroll = gtk_scrolled_window_new(NULL,NULL);
      //  gtk_container_add(GTK_CONTAINER(pWindow),scroll);
        gtk_box_pack_start(GTK_BOX(pVbox),scroll,TRUE,TRUE,0);

        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll),GTK_POLICY_ALWAYS,GTK_POLICY_ALWAYS);
        gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scroll),Image);
        



        //affichage
        gtk_widget_show_all(pWindow);

        //demarrer la boucle evenementielle
        gtk_main();

        printf("Merci pour votre attention!!!\n");

        return EXIT_SUCCESS;

}

void zoomin(GtkWidget *pWidget, gpointer data)
{
    GdkPixbuf *Src, *Dest;
    gint width, height;

    Src = gtk_image_get_pixbuf(GTK_IMAGE(data));

    width = gdk_pixbuf_get_width(Src);
    height = gdk_pixbuf_get_height(Src);

    Dest = gdk_pixbuf_scale_simple(Src,width+1000,height+1000,GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(GTK_IMAGE(data),Dest);

    g_object_unref(Dest);


}

void zoomout(GtkWidget *pWidget, gpointer data)
{
    GdkPixbuf *Src, *Dest;
    gint width, height;
    Src = gtk_image_get_pixbuf(GTK_IMAGE(data));
    width = gdk_pixbuf_get_width(Src);
    height = gdk_pixbuf_get_height(Src);

    Dest = gdk_pixbuf_scale_simple(Src,width-1000,height-1000,GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(GTK_IMAGE(data),Dest);

    g_object_unref(Dest);

}

void on_about_btn(GtkWidget *pBtn,gpointer data)
{
        GtkWidget *about;
        gchar *msg = "message qui affiche :les instructions \n- instructions1\n- instruction2\n- instruction3\n- ...";
        about = gtk_message_dialog_new(GTK_WINDOW(data),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"instructions \n%s",msg);

        gtk_dialog_run(GTK_DIALOG(about));

        gtk_widget_destroy(about);
}

