if (top.location != self.location){top.location=self.location;}
function ReImgSize(){
for (i=0;i<document.images.length;i++)
{
if (document.images[i].width>615)
{
document.images[i].width=615;
}
}
}