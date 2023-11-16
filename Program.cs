using System;
using System.Runtime.InteropServices;

class Program
{
    [DllImport("libmathlib.so")]
    public static extern int add(int a, int b);

    [DllImport("libmathlib.so")]
    public static extern IntPtr subtract(IntPtr a);


    


    static void Main()
    {
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







            // Now you can use 'unmanagedPtr' for interoperability with native code
            // ...

            // For demonstration, let's print the content in unmanaged memory
            /*for (int i = 0; i < byteArray.Length; i++)
            {
                byte value = Marshal.ReadByte(unmanagedPtr, i);
                Console.WriteLine($"Byte at index {i}: 0x{value:X}");
            }*/
        }
        finally
        {
            // Free the allocated unmanaged memory
            Marshal.FreeHGlobal(unmanagedPtr);
        }

}
    }
}
