package com.aikisoft.udpclient;

import android.app.*;
import android.os.*;
import android.view.inputmethod.*;
import org.apache.http.entity.*;
import java.util.*;
import android.view.View.*;

import java.io.IOException; 
import java.net.DatagramPacket; 
import java.net.DatagramSocket; 
import java.net.InetAddress; 
import java.net.SocketException; 
import java.net.UnknownHostException;

import android.os.AsyncTask; 
import android.view.View; 
import android.widget.TextView;
import android.widget.*;
import android.widget.*;
import android.view.View.OnTouchListener;
import android.view.*;
import android.view.View.*;
import android.content.*;
import android.text.*;
import android.graphics.*;

public class MainActivity extends Activity implements OnTouchListener {

		Button btnConnect;
		Button leftButton;
		UDPClient udpClient;
		String udpMsg;
		String coordinates;
		TextView touchPad;
		EditText ipText;
		EditText keyStroke; 
		OnTouchListener leftButtonListener;
		InputMethodManager imm;
		InputMethodSubtype ims;
		TextWatcher softInputHadle;
		
		float x; 
		float y; 
		
		long oldx;
		long oldy;
		
		String sDown; 
		String sMove; 
		String sUp;
		String ip = "192.168.0.100";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
    
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        
        btnConnect = (Button) findViewById (R.id.connect);
        leftButton = (Button) findViewById (R.id.left);
        leftButtonListener = new LeftClick();
        leftButton.setOnTouchListener (leftButtonListener);
       
        touchPad = (TextView) findViewById (R.id.touchpad);
        touchPad.setOnTouchListener(this);
        
        ipText = (EditText) findViewById (R.id.address);
        keyStroke = (EditText) findViewById (R.id.sendData);
        keyStroke.setBackgroundColor(Color.BLACK);  
        keyStroke.dispatchKeyEvent(new KeyEvent(KeyEvent.ACTION_DOWN, KeyEvent.KEYCODE_0));  
        
        imm = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
        ims = imm.getCurrentInputMethodSubtype();  
                
        softInputHadle = new TextWatcher () {
        
        		@Override 
        		public void onTextChanged(CharSequence s, int start, int before, int count) {	
        		
        				if (s.length() > 0) { 
        						        						        						
        						String lastChar = keyStroke.getText().toString(); 
        						lastChar = lastChar.substring(lastChar.length() - 1);
									
									String rus = "04" + Integer.toHexString(lastChar.charAt(0)).substring(1);
									int isRussian = Integer.parseInt(rus, 16);
									
									if (isRussian >= 1024) {	
									
											if (count == 1) {	
									
													udpMsg = "m" + " " + "04" + Integer.toHexString(lastChar.charAt(0)).substring(1);
													//leftButton.setText ("ru");
													udpClient = new UDPClient ();
													udpClient.execute ();
											
											}
											
									}
									
									else {
														
											if (count == 1) {
													
													udpMsg = "m" + lastChar;
													udpClient = new UDPClient ();
													udpClient.execute ();
											
											}
											
											
									
									}
											
									
							}		
							
					}

					@Override 
					public void beforeTextChanged(CharSequence s, int start, int count, int after) {
							 
								
									
					}

					@Override 
					public void afterTextChanged(Editable s) {																
																		
							if (s.length() == 0)	{							
									s.append('\b');
        				}
															
							if (s.length() > 1)	 {
									s.delete(0, 1);
							}		
												
					}
        
        };
        
        
        keyStroke.addTextChangedListener(softInputHadle);
		
		}
		
		private int clickCount = 0;  		
  		private long startTime, duration;
  		static final int maxDuration = 200;
  
    @Override 
    public boolean onTouch (View v, MotionEvent event) { 
    
    		oldx = (long)x;
    		oldy = (long)y;	
    
    		x = event.getX(); 
    		y = event.getY();

			switch (event.getAction()) { 
			
					case MotionEvent.ACTION_DOWN: // нажатие 
							
							if (btnConnect.getVisibility() == View.VISIBLE) {
	  								btnConnect.setVisibility(View.GONE);
	  								ipText.setVisibility(View.GONE);
	  						}
	  						
							View view = this.getCurrentFocus(); if (view != null) {
									imm.hideSoftInputFromWindow(view.getWindowToken(),0);
							}

					
					
	  						
							startTime = System.currentTimeMillis();
							clickCount++;
							
							break; 
							
					case MotionEvent.ACTION_MOVE:		
																				
							udpMsg = "" + (long)x + " " + (long)y + " " + oldx + " " + oldy;
							udpClient = new UDPClient ();
							udpClient.execute ();
							 						
							break; 
							
					case MotionEvent.ACTION_UP:
					
							long clickTime = System.currentTimeMillis() - startTime;							
							duration += clickTime;
							
							
							if (clickTime < 150) {

									udpMsg = "l";
									udpClient = new UDPClient ();
									udpClient.execute ();
 
							}

							
							/*if (clickCount == 2) {
							
									if (duration <= maxDuration) {
											
											udpMsg = "d";
											udpClient = new UDPClient ();
											udpClient.execute ();
									
									}
									
									clickCount = 0;
									duration = 0;
							
							}*/
														
							break;	
					} 
			
			
			
			
			return true; 
			
		} 
    
    public void onclick(View v) {

				ip = ipText.getText().toString();
								
	  }		
	  
	  
	  public void keyBoard (View v) {

				//keyStroke.setVisibility(View.VISIBLE);
				btnConnect.setVisibility(View.GONE);
	  			ipText.setVisibility(View.GONE);
	  			
				keyStroke.requestFocus();				
				imm.toggleSoftInput(InputMethodManager.SHOW_FORCED,0);				
				//keyStroke.setText ("text");
				
				
				

				
	  }		
	  
	  public void switchComputer (View v) {
	  
	  			if (btnConnect.getVisibility() == View.VISIBLE) {
	  					btnConnect.setVisibility(View.GONE);
	  					ipText.setVisibility(View.GONE);
	  			}		
	  					
	  			else if (btnConnect.getVisibility() == View.GONE) {		
	  					btnConnect.setVisibility(View.VISIBLE);
	  					ipText.setVisibility(View.VISIBLE);
	  			}			
	  
	  }

	  
	  public void leftClick(View v) {

				//Toast toast = Toast.makeText(getApplicationContext(), "leftClick", Toast.LENGTH_SHORT); 
				//toast.show();
													
	  }		
	  
	  public void rightClick(View v) {

				//btnConnect.setEnabled(false);
				udpMsg = "r";
				udpClient = new UDPClient ();
				udpClient.execute ();
				//touchPad.setText("click");
				//runUdpClient ();
				
	  }		

		class LeftClick implements OnTouchListener {
		
				@Override 
    			public boolean onTouch (View v, MotionEvent event) { 
    
						switch (event.getAction()) { 
					
								case MotionEvent.ACTION_DOWN:  
									
										//leftClick(leftButton);
										udpMsg = "d";
										udpClient = new UDPClient ();
										udpClient.execute ();	
							
										break; 
																
								case MotionEvent.ACTION_UP:
							
										udpMsg = "u";
										udpClient = new UDPClient ();
										udpClient.execute ();					
															
										break;
										
						}
						
						return true;
				
				}				
						
		}
		  
		  
    	class UDPClient extends AsyncTask <Void, Void, Void> {
    	
    			

				@Override 
				protected Void doInBackground (Void... params) { 
						
						
						runUdpClient (udpMsg);
						return null;
						 
				}
				
			/*	@Override 
				protected void onPostExecute (Void result) { 
						
						super.onPostExecute(result);

				}*/

			 
				
    	}
    
    
  	 	private static final int UDP_SERVER_PORT = 8888; 
	
		private void runUdpClient (String direction) { 
		
				//String udpMsg = "hello world from UDP client " + UDP_SERVER_PORT; 
				DatagramSocket ds = null; 
				
				try { 
						
					//	String a = (Peer) peer;
						
						ds = new DatagramSocket(); 
						InetAddress serverAddr = InetAddress.getByName(ip); 
						DatagramPacket dp; 
						dp = new DatagramPacket(direction.getBytes(), direction.length(), serverAddr, UDP_SERVER_PORT); 
						ds.send(dp); 
												
				} 
					
				catch (SocketException e) { 
						//Toast toast = Toast.makeText(getApplicationContext(), "Socket exeption", Toast.LENGTH_SHORT); 
						//toast.show();
					   System.err.println( "Exception occurred:" + e.toString()); 
					   e.printStackTrace();
						//e.printStackTrace(); 
				}
				
				catch (UnknownHostException e) { 
						e.printStackTrace(); 
					//	Toast toast = Toast.makeText(getApplicationContext(), "Unknown host exeption", Toast.LENGTH_SHORT); 
					//	toast.show();

				} 
				
				catch (IOException e) { 
						e.printStackTrace(); 
					//	Toast toast = Toast.makeText(getApplicationContext(), "IO exeption", Toast.LENGTH_SHORT); 
					//	toast.show();

				} 
				
				catch (Exception e) { 
						System.err.println( "Exception occurred:" + e.toString()); 
						e.printStackTrace(); 
						
						//Toast toast = Toast.makeText(getApplicationContext(), "Exeption", Toast.LENGTH_SHORT); 
						//toast.show();

				} 
				
				finally { 
						
						if (ds != null) { 
								ds.close(); 
						}
						 
				} 
	
		} 

    
}


