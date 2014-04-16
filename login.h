int check_login_proc(int msg, DIALOG *d, int c)
{
      int ret;

      //call the parent object
      ret = d_button_proc(msg, d, c);

      //check the return value
      if (ret == D_EXIT) {
        
        if (checkLogin(name, pass))
            alert("Logging In", NULL, NULL, "OK", NULL, 'y', NULL);
        
        alert("INCORRECT LOGIN", NULL, "Please try again...", "OK", NULL, 'y', NULL);
         return D_REDRAW;
          
      }

      /* otherwise just return */
      return ret;
}

int launch_url_proc1(int msg, DIALOG *d, int c)
{
      int ret;

      /* call the parent object */
      ret = d_button_proc(msg, d, c);

      //open window for the create account button
      if (ret == D_EXIT)
      {
        ShellExecute(NULL, "open", "rundll32", 
            "url.dll, FileProtocolHandler http://www.whiteoakstables.net/create", 
            "", SW_SHOWNOACTIVATE);
            
        return D_REDRAW;
     }

      //otherwise return the screen
      return ret;
}

int launch_url_proc2(int msg, DIALOG *d, int c)
{
      int ret;

      /* call the parent object */
      ret = d_button_proc(msg, d, c);

      //open window for the create account button
      if (ret == D_EXIT)
      {
        ShellExecute(NULL, "open", "rundll32", 
            "url.dll, FileProtocolHandler http://www.whiteoakstables.net/lost", 
            "", SW_SHOWNOACTIVATE);
            
        return D_REDRAW;
     }

      //otherwise return the screen
      return ret;
}

int launch_url_proc3(int msg, DIALOG *d, int c)
{
      int ret;

      /* call the parent object */
      ret = d_button_proc(msg, d, c);

      //open window for the create account button
      if (ret == D_EXIT)
      {
        ShellExecute(NULL, "open", "rundll32", 
            "url.dll, FileProtocolHandler http://www.whiteoakstables.net/help", 
            "", SW_SHOWNOACTIVATE);
            
        return D_REDRAW;
     }

      //otherwise return the screen
      return ret;
}

int checkLogin(char *name, char *pass)
{
    alert("Checking login...", NULL, NULL, "OK", NULL, 'y', NULL);
    return 0; 
}
