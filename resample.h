#ifndef _Resample_h
#define _Resample_h
#include <samplerate.h>
#include <map>
#include <stdint.h>
#include <cstddef>

extern "C" {

    char* resample(
        char* source_audio_buffer,       //Input array
        int input_frames,  //Input frames
        int output_frames,
        double ratio, uint32_t node_id);

    class ResampleManager
    {
        const int INPUT_FRAMES = 320;
        double m_ratio = 1.0;
    public:
        ResampleManager(double ratio = 1.0) : m_ratio(ratio)
        {
            int output_cout = INPUT_FRAMES * ratio;
            m_converter_input = new float[INPUT_FRAMES];
            m_converter_output = new float[output_cout];
            m_output_buffer = new short[output_cout];
            int error;
            m_src_state = src_new(SRC_SINC_FASTEST, 1, &error);
        }
        static  char* ResampleData(char* source_audio_buffer,       //Input array
            int input_frames,  //Input frames
            int output_frames,
            double ratio, uint32_t node_id);
        char* _ResampleData(char* input_buffer,       //Input array
            int input_frames,  //Input frames
            int output_frames, //Output Frames,
            double ratio,
            int end_of_input,
            bool& res);
    private:
        SRC_STATE* m_src_state = nullptr;
        float* m_converter_input = nullptr;
        float* m_converter_output = nullptr;
        short* m_output_buffer = nullptr;
    private:
        static std::map<uint32_t, ResampleManager*> m_nodesResampleInfo;
        void shortArrayToFloatArray(short* source, float* dest, size_t samples);
        void floatArrayToShortArray(float* source, short* dest, size_t samples);
    };
#endif
}