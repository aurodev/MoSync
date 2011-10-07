using System;
using System.IO;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.GamerServices;
using System.Windows;
using System.Threading;

namespace MoSync
{	
	class Util {
		
		public static uint NextPowerOfTwo(int minPow, uint val) {
			uint i = (uint)(1 << minPow);
			while(i < val) {
				i <<= 1;		
			}
			return i;			
		}
		
		public static sbyte StreamReadInt8(Stream stream) {
			return (sbyte)stream.ReadByte();
		}
			
		public static short StreamReadInt16(Stream stream) {
			int a = stream.ReadByte();
			int b = stream.ReadByte();
			return (short)(b << 8 | a);			
		}	
		
		public static int StreamReadInt32(Stream stream) {
			int a = stream.ReadByte();
			int b = stream.ReadByte();
			int c = stream.ReadByte();
			int d = stream.ReadByte();
			return d << 24 | c << 16 | b << 8 | a;			
		}
		
		public static byte StreamReadUint8(Stream stream) {
			return (byte)stream.ReadByte();
		}
			
		public static ushort StreamReadUint16(Stream stream) {
			int a = stream.ReadByte();
			int b = stream.ReadByte();
			return (ushort)(b << 8 | a);			
		}	
		
		public static uint StreamReadUint32(Stream stream) {
			int a = stream.ReadByte();
			int b = stream.ReadByte();
			int c = stream.ReadByte();;
			int d = stream.ReadByte();
			return (uint)(d << 24 | c << 16 | b << 8 | a);			
		}

        public static double ConvertToDouble(int a, int b)
        {
            /*
            ulong value = (ulong)a;
            value <<= 32;
            value |= (uint)b;
            */
            ulong value = (ulong)b;
            value <<= 32;
            value |= (uint)a;

            double retVal = BitConverter.Int64BitsToDouble((long)value);
            return retVal;
        }

        public static float ConvertToFloat(int a)
        {
            return BitConverter.ToSingle(BitConverter.GetBytes(a), 0);
        }
		
		public static void Log(String text)
		{
			Console.Write(text);
		}
		
		public static void CriticalError(String text) {
			Log(text);
			//System.Environment.Exit(1);
            //MessageBox.Show(text);
            Deployment.Current.Dispatcher.BeginInvoke(() => MessageBox.Show(text));
            //throw new Exception("ExitAppException");
		}

        public static int CreateExtent(int w, int h) 
        {
            return (w << 16) | h;
        }

        public void RunOnMainThreadBlock(Action action)
        {
            using (AutoResetEvent are = new AutoResetEvent(false))
            {
                Deployment.Current.Dispatcher.BeginInvoke(() =>
                {
                    action();
                    are.Set();
                });
                are.WaitOne();
            }
        }
	}
}

