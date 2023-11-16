#include "resample.h"
#include <cstring>




char* resample(
    char* source_audio_buffer,       //Input array
    int input_frames,  //Input frames
    int output_frames,
    double ratio, uint32_t node_id)
{
    return ResampleManager::ResampleData(
        source_audio_buffer,       //Input array
        input_frames,  //Input frames
        output_frames,
        ratio, 
        node_id);
}


std::map<uint32_t, ResampleManager*> ResampleManager::m_nodesResampleInfo;
char* ResampleManager::ResampleData(char* source_audio_buffer,       //Input array
    int input_frames,  //Input frames
    int output_frames,
    double ratio, uint32_t node_id)
{
    ResampleManager* resampleManager = nullptr;
    auto iter = m_nodesResampleInfo.find(node_id);
    if (iter == m_nodesResampleInfo.end())
    {
        resampleManager = new ResampleManager(ratio);
        m_nodesResampleInfo.insert({ node_id, resampleManager });
    }
    else
        resampleManager = iter->second;
    int end_of_input = 0;
    bool conv_res;
    char* final = resampleManager->_ResampleData(source_audio_buffer, input_frames, output_frames, ratio, end_of_input, conv_res);
    return final;
}

char* ResampleManager::_ResampleData(char* input_buffer,       //Input array
    int input_frames,  //Input frames
    int output_frames, //Output Frames,
    double ratio,
    int end_of_input,
    bool& res)
{
    short* sourceData = reinterpret_cast<short*>(input_buffer);
    shortArrayToFloatArray(sourceData, m_converter_input, input_frames);

    /* Prepare SRC_DATA */
    SRC_DATA src_data;
    memset(&src_data, 0, sizeof(src_data));
    src_data.data_in = m_converter_input;
    src_data.input_frames = input_frames;

    src_data.data_out = m_converter_output;
    src_data.output_frames = output_frames;

    src_data.src_ratio = ratio;
    src_data.end_of_input = end_of_input;

    /* Process! */
    int srcresult = src_process(m_src_state, &src_data);
    int err = src_error(m_src_state);

    floatArrayToShortArray(m_converter_output, m_output_buffer, output_frames);
    res = srcresult == 0 && err == 0;
    char* final_out = reinterpret_cast<char*>(m_output_buffer);
    return final_out;
}

void ResampleManager::shortArrayToFloatArray(short* source, float* dest, size_t samples)
{
    size_t sampleIndex = 0;
    for (sampleIndex = 0; sampleIndex < samples; sampleIndex++)
    {
        float dst = float(source[sampleIndex]) / 0x8000;

        if (dst > 1.0) dst = 1.0;
        if (dst < -1.0) dst = -1.0;
        dest[sampleIndex] = dst;
    }
}

void ResampleManager::floatArrayToShortArray(float* source, short* dest, size_t samples)
{
    size_t sampleIndex = 0;
    for (sampleIndex = 0; sampleIndex < samples; sampleIndex++)
    {
        float f = source[sampleIndex] * 32768;
        if (f > 32767) f = 32767;
        if (f < -32768) f = -32768;
        dest[sampleIndex] = (short)f;
    }
}
