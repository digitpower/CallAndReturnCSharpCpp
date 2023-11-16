using System;
using System.Runtime.InteropServices;

class Program
{
    [DllImport("libmathlib.so")]
    public static extern IntPtr resample(
        IntPtr source_audio_buffer,       //Input array
        int input_frames,  //Input frames
        int output_frames,
        double ratio, 
        uint node_id
    );


    


    static void Main()
    {
/*
        for(int i = 0;i < 10; i++)
        {




        // Example byte array
        byte[] byteArray = { 0x41, 0x42, 0x43, 0x44 };

        // Allocate unmanaged memory
        IntPtr unmanagedPtr = Marshal.AllocHGlobal(byteArray.Length);

        try
        {
            // Copy the byte array to unmanaged memory
            Marshal.Copy(byteArray, 0, unmanagedPtr, byteArray.Length);



            int resultAdd = add(5, 3);
            IntPtr resultSubtract = subtract(unmanagedPtr);

            Console.WriteLine($"Addition result: {resultAdd}");






            // Copy the unmanaged memory into a managed byte array
            byte[] byteArrayRes = new byte[4];
            Marshal.Copy(resultSubtract, byteArrayRes, 0, byteArrayRes.Length);

            // Print the content of the byte array
            Console.WriteLine("Byte Array Content:");
            foreach (byte value in byteArrayRes)
            {
                Console.Write($"{value:X2} ");
            }
            Console.WriteLine();







        }
        finally
        {
            // Free the allocated unmanaged memory
            Marshal.FreeHGlobal(unmanagedPtr);
        }
    }
    */


        byte[] audioData = new byte[440*32];
        IntPtr unmanagedPtrAudio = Marshal.AllocHGlobal(audioData.Length);
        Marshal.Copy(audioData, 0, unmanagedPtrAudio, audioData.Length);

        IntPtr resampledAudioPtr = resample(
            unmanagedPtrAudio,       //Input array
            16*440,  //Input frames
            8*440, //Output frames
            0.5, //ratio 
            123456 //node_id
        );

    }
}
