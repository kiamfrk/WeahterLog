/*
IMPORTANT NOTE about TembooAccount.h

TembooAccount.h contains your Temboo account information and must be included
alongside your sketch. To do so, make a new tab in Arduino, call it TembooAccount.h,
and copy this content into it. 
*/

#define TEMBOO_ACCOUNT "uriche"  // Your Temboo account name 
#define TEMBOO_APP_KEY_NAME "myFirstApp"  // Your Temboo app key name
#define TEMBOO_APP_KEY "e7UdSLWc3nSmrj6eOVUbf9IM20LiUCOz"  // Your Temboo app key


#define GOOGLE_CLIENT_ID "45712978547-fj9e1nl7ae84e86d8srmssfq75kun73g.apps.googleusercontent.com"
#define GOOGLE_CLIENT_SECRET "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"
#define GOOGLE_CLIENT_REFRESH_TOKEN "1//0dJq2DRWtDN13CgYIARAAGA0SNwF-L9IrHgUGdrER94kkGrSiVxKr8euUdmA7mzxRydnVjXc4F14RSKsH1yELSDkWS-yJOoRVmsk"
#define GOOGLE_SPREADSHEET_ID "1YIHLM_pbOZqU4_DD50s-SlE_1Q6b7FCfbTnPb_bGQE4" 

#if TEMBOO_LIBRARY_VERSION < 2
#error "Your Temboo library is not up to date. You can update it using the Arduino library manager under Sketch > Include Library > Manage Libraries..."
#endif

/* 
The same TembooAccount.h file settings can be used for all Temboo SDK sketches.  
Keeping your account information in a separate file means you can share the 
main .ino file without worrying that you forgot to delete your credentials.
*/
