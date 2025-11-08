#include <cstdlib>
#include <gtk/gtk.h>
#include <iostream>
#include <string>
#include <webkit2/webkit2.h>

static void on_window_destroy(GtkWidget * /*widget*/, gpointer /*data*/) {
  gtk_main_quit();
}

static gboolean on_close_webview(WebKitWebView * /*webview*/,
                                 GtkWidget *window) {
  gtk_widget_destroy(window);
  return TRUE;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Usage: typstview <url>\n";
    std::cerr << "Example: typstview http://127.0.0.1:23625\n";
    return 1;
  }

  std::string url = argv[1];

  if (url.rfind("http://", 0) != 0 && url.rfind("https://", 0) != 0) {
    std::cerr << "Error: URL must start with http:// or https://\n";
    return 1;
  }

  // Initialize GTK
  gtk_init(&argc, &argv);

  // Create main window
  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Typst Preview");
  gtk_window_set_default_size(GTK_WINDOW(window), 1000, 800);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);

  WebKitWebView *webview = WEBKIT_WEB_VIEW(webkit_web_view_new());

  WebKitSettings *settings = webkit_web_view_get_settings(webview);
  webkit_settings_set_enable_javascript(settings, TRUE);
  webkit_settings_set_javascript_can_access_clipboard(settings, TRUE);

  // Enable developer extras only in debug mode
  const char *debug_env = std::getenv("TYPST_DEBUG");
  if (debug_env && std::string(debug_env) == "1") {
    webkit_settings_set_enable_developer_extras(settings, TRUE);
  } else {
    webkit_settings_set_enable_developer_extras(settings, FALSE);
  }

  g_signal_connect(webview, "close", G_CALLBACK(on_close_webview), window);
  gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(webview));
  webkit_web_view_load_uri(webview, url.c_str());
  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}
