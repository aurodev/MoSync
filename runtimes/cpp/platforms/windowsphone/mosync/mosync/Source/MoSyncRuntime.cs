using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
using System.Windows.Media.Imaging;
using System.Windows;
using System.Threading;
using System.Reflection;
using System.Windows.Input;

namespace MoSync
{
    // This is an interface for each group of syscalls.
    // Whenever a class implements this interface it
    // will be registered as a syscall module.
    // Each syscall module in the program
    // will be instansiated once. Directly afterwards the
    // Init function will be executed. There you
    // should set those delegates corresponding to the
    // group in the Syscalls instance to an implementation.

    public interface ISyscallGroup
    {
        void Init(Syscalls syscalls, Core core, Runtime runtime);
    }

    // This is the runtime
    // It has a Syscalls instance which contains
    // delegates to the implementations of all syscalls
    // it also loads and manages resources
    public partial class Runtime
    {
        private List<ISyscallGroup> mSyscallGroups = new List<ISyscallGroup>();
        private List<Memory> mEvents = new List<Memory>();
        private test_mosync.MainPage mMainPage;

        private void InitSyscalls()
        {

            // find all classes that implements the ISyscallGroup interface
            // and make an instance of each and call their Init method.
            foreach (Type t in Assembly.GetCallingAssembly().GetTypes())
            {
                if (t.GetInterface("MoSync.ISyscallGroup", false) != null)
                {
                    ISyscallGroup instance = Activator.CreateInstance(t) as ISyscallGroup;
                    mSyscallGroups.Add(instance);
                    instance.Init(mSyscalls, mCore, this);
                }
            }

        }
  
        public Runtime(Core core, test_mosync.MainPage mainPage)
        {
            mMainPage = mainPage;

            mainPage.MouseLeftButtonDown += delegate(Object sender, MouseButtonEventArgs e)
            {
                Memory mem = new Memory(4 * 3);
                mem.WriteInt32(0, MoSync.Constants.EVENT_TYPE_POINTER_PRESSED);
                mem.WriteInt32(4, 0); // x
                mem.WriteInt32(8, 0); // y
                PostEvent(mem);
            };

            mainPage.MouseLeftButtonUp += delegate(Object sender, MouseButtonEventArgs e)
            {
                Memory mem = new Memory(4 * 3);
                mem.WriteInt32(0, MoSync.Constants.EVENT_TYPE_POINTER_RELEASED);
                mem.WriteInt32(4, 0); // x
                mem.WriteInt32(8, 0); // y
                PostEvent(mem);
            };

            mCore = core;
            mSyscalls = new Syscalls();

            InitSyscalls();

            mSyscalls.maGetEvent = delegate(int ptr)
            {
                if (mEvents.Count != 0)
                {
                    Memory mem = mEvents[0];
                    mEvents.RemoveAt(0);
                    mCore.GetDataMemory().WriteMemoryAtAddress(ptr, mem, 0, mem.GetSizeInBytes());
                    return 1;
                }
                else
                {
                    return 0;
                }
            };
        }

        public test_mosync.MainPage GetMainPage()
        {
            return mMainPage;
        }

        // will reset the runtime.
        public void Init()
        {
        }

        public void PostEvent(Memory memory)
        {
            mEvents.Add(memory);
        }

        // resource specific packed integer.
        private uint ReadUnsignedVarInt(Stream file)
        {
            uint res = 0;
            int nBytes = 0;
            while (true)
            {
                uint b = MoSync.Util.StreamReadUint8(file);
                res |= (b & 0x7f) << (nBytes * 7);
                if (b > 0x7f)
                    break;
                nBytes++;
                if (nBytes >= 4)
                {
                    // fail
                    return 0;
                }
            }
            return res;
        }

        public bool LoadResources(Stream file)
        {
            if (MoSync.Util.StreamReadInt8(file) != 'M')
                return false;
            if (MoSync.Util.StreamReadInt8(file) != 'A')
                return false;
            if (MoSync.Util.StreamReadInt8(file) != 'R')
                return false;
            if (MoSync.Util.StreamReadInt8(file) != 'S')
                return false;

            uint numResources = ReadUnsignedVarInt(file);
            uint resSize = ReadUnsignedVarInt(file);
            
            
            mCurrentResourceHandle = 1;

            while (true)
            {
                byte type = MoSync.Util.StreamReadUint8(file);
                if (type == 0) break;

                uint size = ReadUnsignedVarInt(file);

                Resource resource = new Resource(null, type);
                mResources.Add(mCurrentResourceHandle, resource);

                switch (type)
                {
                    case MoSync.Constants.RT_PLACEHOLDER:

                        break;
                    case MoSync.Constants.RT_UBIN:
                    case MoSync.Constants.RT_BINARY:
                        Memory memory = new Memory((int)size);
                        memory.WriteFromStream(0, file, (int)size);
                        resource.SetInternalObject(memory);
                        break;
                    case MoSync.Constants.RT_IMAGE:
                        byte[] bytes = new byte[size];
                        file.Read(bytes, 0, (int)size);
                        using (MemoryStream ms = new MemoryStream(bytes, 0, bytes.Length))
                        {
                            BitmapImage im = new BitmapImage();
                            im.CreateOptions = BitmapCreateOptions.None;
                            im.SetSource(ms);
                            WriteableBitmap wb = new WriteableBitmap(im); 
                            resource.SetInternalObject(wb);
                        }
                        break;
                }

                mCurrentResourceHandle++;
            }

            return true;
        }

        public Syscalls GetSyscalls()
        {
            return mSyscalls;
        }

        public Resource GetResource(int type, int handle)
        {
            Resource ret;
            if (!mResources.TryGetValue(handle, out ret))
            {
                return null;
            }
            else
            {
                if (ret.GetResourceType() != type)
                    return null;
                return ret;
            }
        }

        public void SetResource(int handle, Resource res)
        {
            mResources.Add(handle, res);
        }

        public int AddResource(Resource res)
        {
            mResources.Add(mCurrentResourceHandle++, res);
            return mCurrentResourceHandle - 1;
        }

        protected Core mCore;
        protected Syscalls mSyscalls;
        protected Dictionary<int, Resource> mResources = new Dictionary<int, Resource>();
        protected int mCurrentResourceHandle;
    }
}

