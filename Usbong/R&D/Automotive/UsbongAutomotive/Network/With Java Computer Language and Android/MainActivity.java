/*
' Copyright 2014~2021 USBONG SOCIAL SYSTEMS, INC. (USBONG)
'
' Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You ' may obtain a copy of the License at
'
' http://www.apache.org/licenses/LICENSE-2.0
'
' Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, ' WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing ' permissions and limitations under the License.
'
' @company: USBONG SOCIAL SYSTEMS, INC. (USBONG)
' @author: Michael Syson
' @date created: 20140703
' @date updated: 20210327
'
' Notes:
' 1) We use this set of instructions to execute:
' 1.1) Image to String 
' 1.2) String to Image
'
' 2) This is the only file from the src folder of the project;
' The project's assets, res, et cetera are another set of folders
'
' Acknowledgment:
' 1) Westpac company, et al.
*/

package usbong.halimbawa;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;

import android.app.Activity;
import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.Bitmap.CompressFormat;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.util.Base64;
import android.util.Log;
import android.view.Menu;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.RelativeLayout.LayoutParams;

public class MainActivity extends Activity {

	protected FrameLayout.LayoutParams lp;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		init();
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	public void init() {
		lp = new FrameLayout.LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);

		//why base 64? for compactness. One character can have 64 possible values.
		
		// get the base 64 string
		String imgString = Base64.encodeToString(getBytesFromBitmap(getBitmapFromAsset("mike.png")),//someImg), 
		                       Base64.NO_WRAP);

		Log.d(">>>>> imgString",imgString);
		
		
		//Reference: http://stackoverflow.com/questions/4837110/how-to-convert-a-base64-string-into-a-bitmap-image-to-show-it-in-a-imageview;
		//last accessed: 3 July 2014; answer by User432209
		//decode string -> byte[] -> bitmap
		byte[] decodedString = Base64.decode(/*encodedImage*/imgString, Base64.DEFAULT);
		Bitmap decodedByte = BitmapFactory.decodeByteArray(decodedString, 0, decodedString.length);
		
		try {
			//Reference: http://stackoverflow.com/questions/12320857/how-to-get-my-activity-context;
			//last accessed: 3 July 2014; answer by Gan
			Context c = getApplicationContext();
			ImageView myImageView = new ImageView(c);
			myImageView.setImageBitmap(decodedByte);
			this.addContentView(myImageView, lp); 		
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	//Reference: http://stackoverflow.com/questions/10513976/how-to-convert-image-into-byte-array-and-byte-array-to-base64-string-in-android;
	//last accessed: 3 July 2014; answer by Dhruv Gairola
	// convert from bitmap to byte array
	public byte[] getBytesFromBitmap(Bitmap bitmap) {
	    ByteArrayOutputStream stream = new ByteArrayOutputStream();
	    bitmap.compress(CompressFormat.JPEG, 70, stream);
	    return stream.toByteArray();
	}
	
	//Reference: http://stackoverflow.com/questions/18973550/load-images-from-assets-folder;
	//last accessed: 3 July 2014; answer by Lokesh
	private Bitmap getBitmapFromAsset(String strName)
    {
        AssetManager assetManager = getAssets();
        InputStream istr = null;
        try {
            istr = assetManager.open(strName);
        } catch (IOException e) {
            e.printStackTrace();
        }
        Bitmap bitmap = BitmapFactory.decodeStream(istr);
        return bitmap;
    }
}
