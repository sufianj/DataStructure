document.body.oncopy = function () { 
	setTimeout( function () { 
		var text = clipboardData.getData("text");
		if (text) { 
			text=text+"\r\n�������ԣ�"+location.href; clipboardData.setData("text", text);
		} 
	}, 100 ) 
}