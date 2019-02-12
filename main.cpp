#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;
using namespace std;
int main()
{
    VideoCapture camera(1);
    Mat frame;
    Mat output;
    Point BottomLeft = Point (78, 421);
    Point TopLeft=Point(311,163);
    Point BottomRight=Point(636,465);
    Point TopRight=Point(596,178);

    const int maxwidth = 500;
    const int maxheight = 500;

    while (1) {
        camera >> frame;
        circle(frame,BottomRight,5,(255,0,255),5);//2번쨰 값은 point값으로 넘겨주어야함
        circle(frame,BottomLeft,5,(255,0,255),5);
        circle(frame,TopRight,5,(255,0,255),5);
        circle(frame,TopLeft,5,(255,0,255),5);

        Point2f src[4],dst[4];
        src[0]=Point2f(TopLeft.x,TopLeft.y);
        src[1]=Point2f(TopRight.x,TopRight.y);
        src[2]=Point2f(BottomRight.x,BottomRight.y);
        src[3]=Point2f(BottomLeft.x,BottomLeft.y);

        dst[0]=Point2f(0,0);
        dst[1]=Point2f(maxwidth-1,0);
        dst[2]=Point2f(maxwidth-1,maxheight-1);
        dst[3]=Point2f(0, maxheight-1);

        Mat transform = getPerspectiveTransform(src, dst);//getPerspectiveTransform을 사용하려면 대응점들의 좌표를 알려주어야한다.
        warpPerspective(frame,output,transform,Size(maxwidth,maxheight));//밀집투시변환함수
        imshow("affine",output);
        imshow("Nomal",frame);
        if ( waitKey(1) == 27)break;
    }
}
