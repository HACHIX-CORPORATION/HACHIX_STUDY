#undef TEST_DELIGATE
#define TEST_EVENT

using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace StudyCode
{

    static class Program
    {
        /// <summary>
        /// アプリケーションのメイン エントリ ポイントです。
        /// </summary>
        [STAThread]
        static void Main()
        {
#if TEST_DELIGATE
            var processor = new PhotoProcessor();
            var filter = new PhotoFilter();
            PhotoProcessor.PhotoFilterHandler filterHandler = filter.AppplyBrightness;
            filterHandler += filter.AppplyConstrast;
            filterHandler += RemoveRedEye;

            processor.Process2("photo.jpg", filterHandler);
#endif

#if TEST_EVENT
            var video = new Video() { Title = "Video1"};
            var videoEncoder = new VideoEncoder(); // publisher
            var mailService = new MailService();    // subscriber

            videoEncoder.VideoEncoded += mailService.OnVideoEncoded;
            videoEncoder.Encode(video);
#endif
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }

        static void RemoveRedEye(Photo photo)
        {
            Console.WriteLine("RemoveRedEye");
        }
    }

    public class MailService
    {
        public void OnVideoEncoded(object source, EventArgs e)
        {
            Console.WriteLine("OnVideoEncoded");
        }
    }
}
