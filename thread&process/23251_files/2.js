document.body.oncopy = function () { 
	setTimeout( function () { 
		var text = clipboardData.getData("text");
		if (text) { 
			text=text+"\r\n本文来自："+location.href; clipboardData.setData("text", text);
		} 
	}, 100 ) 
}