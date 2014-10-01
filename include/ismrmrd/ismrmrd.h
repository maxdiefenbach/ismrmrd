/* ISMRMRD MR Raw Data Strutures                           */
/* DRAFT                                                   */
/* Authors:                                                */
/*    Michael S. Hansen (michael.hansen@nih.gov)           */
/*    Brian Hargreaves  (bah@stanford.edu)                 */
/*    Sebastian Kozerke (kozerke@biomed.ee.ethz.ch)        */
/*    Kaveh Vahedipour  (k.vahedipour@fz-juelich.de)       */
/*    Hui Xue           (hui.xue@nih.gov)                  */
/*    Souheil Inati     (souheil.inati@nih.gov)            */
/*    Joseph Naegele    (joseph.naegele@nih.gov)           */

/**
 * @file ismrmrd.h
 * @defgroup capi C API
 * @defgroup cxxapi C++ API
 */

#pragma once
#ifndef ISMRMRD_H
#define ISMRMRD_H

/* Language and cross platform section for defining types */
/* integers */
#ifdef _MSC_VER /* MS compiler */
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else /* non MS C or C++ compiler */
#include <stdint.h>
#include <stddef.h>     /* for size_t */
#endif /* _MSC_VER */

/* Complex numbers */
#ifdef __cplusplus
#include <complex>
typedef std::complex<float> complex_float_t;
typedef std::complex<double> complex_double_t;
#else
#ifdef _MSC_VER /* MS C compiler */
typedef struct complex_float_t{
    float real;
    float imag;
}complex_float_t;
typedef struct complex_double_t{
    double real;
    double imag;
}complex_double_t;
#else /* C99 compiler */
#include <complex.h>
typedef float complex complex_float_t;
typedef double complex complex_double_t;
#endif /* _MSC_VER */
#endif /* __cplusplus */

/* Booleans - part of C++ */
#ifndef __cplusplus
#ifdef _MSC_VER /* MS C compiler */
typedef int bool;
#define false 0
#define true 1
#else /* C99 compiler */
#include <stdbool.h>
#endif /* _MSC_VER */
#endif /* __cplusplus */

/* Vectors */
#ifdef __cplusplus
#include <vector>
#endif /* __cplusplus */

/* Exports needed for MS C++ */
#include "ismrmrd/export.h"

#pragma pack(push, 2) /* Use 2 byte alignment */

#ifdef __cplusplus
namespace ISMRMRD {
extern "C" {
#endif

/**
 * Constants
 */
enum ISMRMRD_Constants {
    ISMRMRD_VERSION = 1,
    ISMRMRD_USER_INTS = 8,
    ISMRMRD_USER_FLOATS = 8,
    ISMRMRD_PHYS_STAMPS = 3,
    ISMRMRD_CHANNEL_MASKS = 16,
    ISMRMRD_NDARRAY_MAXDIM = 7,
    ISMRMRD_POSITION_LENGTH = 3,
    ISMRMRD_DIRECTION_LENGTH = 3
};


/**
 * Constants
 */
enum ISMRMRD_ErrorCodes {
    ISMRMRD_BEGINERROR=-1,
    ISMRMRD_NOERROR,
    ISMRMRD_MEMORYERROR,
    ISMRMRD_FILEERROR,
    ISMRMRD_TYPEERROR,
    ISMRMRD_RUNTIMEERROR,
    ISMRMRD_ENDERROR
};

/**
 * Data Types
 */
enum ISMRMRD_DataTypes {
    ISMRMRD_USHORT   = 1, /**< corresponds to uint16_t */
    ISMRMRD_SHORT    = 2, /**< corresponds to int16_t */
    ISMRMRD_UINT     = 3, /**< corresponds to uint32_t */
    ISMRMRD_INT      = 4, /**< corresponds to int32_t */
    ISMRMRD_FLOAT    = 5, /**< corresponds to float */
    ISMRMRD_DOUBLE   = 6, /**< corresponds to double */
    ISMRMRD_CXFLOAT  = 7, /**< corresponds to complex float */
    ISMRMRD_CXDOUBLE = 8, /**< corresponds to complex double */
};

/**
 * Acquisition Flags
 */
enum ISMRMRD_AcquisitionFlags {
    ISMRMRD_ACQ_FIRST_IN_ENCODE_STEP1               =  1,
    ISMRMRD_ACQ_LAST_IN_ENCODE_STEP1                =  2,
    ISMRMRD_ACQ_FIRST_IN_ENCODE_STEP2               =  3,
    ISMRMRD_ACQ_LAST_IN_ENCODE_STEP2                =  4,
    ISMRMRD_ACQ_FIRST_IN_AVERAGE                    =  5,
    ISMRMRD_ACQ_LAST_IN_AVERAGE                     =  6,
    ISMRMRD_ACQ_FIRST_IN_SLICE                      =  7,
    ISMRMRD_ACQ_LAST_IN_SLICE                       =  8,
    ISMRMRD_ACQ_FIRST_IN_CONTRAST                   =  9,
    ISMRMRD_ACQ_LAST_IN_CONTRAST                    = 10,
    ISMRMRD_ACQ_FIRST_IN_PHASE                      = 11,
    ISMRMRD_ACQ_LAST_IN_PHASE                       = 12,
    ISMRMRD_ACQ_FIRST_IN_REPETITION                 = 13,
    ISMRMRD_ACQ_LAST_IN_REPETITION                  = 14,
    ISMRMRD_ACQ_FIRST_IN_SET                        = 15,
    ISMRMRD_ACQ_LAST_IN_SET                         = 16,
    ISMRMRD_ACQ_FIRST_IN_SEGMENT                    = 17,
    ISMRMRD_ACQ_LAST_IN_SEGMENT                     = 18,
    ISMRMRD_ACQ_IS_NOISE_MEASUREMENT                = 19,
    ISMRMRD_ACQ_IS_PARALLEL_CALIBRATION             = 20,
    ISMRMRD_ACQ_IS_PARALLEL_CALIBRATION_AND_IMAGING = 21,
    ISMRMRD_ACQ_IS_REVERSE                          = 22,
    ISMRMRD_ACQ_IS_NAVIGATION_DATA                  = 23,
    ISMRMRD_ACQ_IS_PHASECORR_DATA                   = 24,
    ISMRMRD_ACQ_LAST_IN_MEASUREMENT                 = 25,
    ISMRMRD_ACQ_IS_HPFEEDBACK_DATA                  = 26,
    ISMRMRD_ACQ_IS_DUMMYSCAN_DATA                   = 27,
    ISMRMRD_ACQ_IS_RTFEEDBACK_DATA                  = 28,
    ISMRMRD_ACQ_IS_SURFACECOILCORRECTIONSCAN_DATA   = 29,

    ISMRMRD_ACQ_USER1                               = 57,
    ISMRMRD_ACQ_USER2                               = 58,
    ISMRMRD_ACQ_USER3                               = 59,
    ISMRMRD_ACQ_USER4                               = 60,
    ISMRMRD_ACQ_USER5                               = 61,
    ISMRMRD_ACQ_USER6                               = 62,
    ISMRMRD_ACQ_USER7                               = 63,
    ISMRMRD_ACQ_USER8                               = 64
};

/**
 * Image Types
 */
enum ISMRMRD_ImageTypes {
    ISMRMRD_IMTYPE_MAGNITUDE = 1,
    ISMRMRD_IMTYPE_PHASE     = 2,
    ISMRMRD_IMTYPE_REAL      = 3,
    ISMRMRD_IMTYPE_IMAG      = 4,
    ISMRMRD_IMTYPE_COMPLEX   = 5
};

/**
 * Image Flags
 */
enum ISMRMRD_ImageFlags {
    ISMRMRD_IMAGE_IS_NAVIGATION_DATA =  1,
    ISMRMRD_IMAGE_USER1              = 57,
    ISMRMRD_IMAGE_USER2              = 58,
    ISMRMRD_IMAGE_USER3              = 59,
    ISMRMRD_IMAGE_USER4              = 60,
    ISMRMRD_IMAGE_USER5              = 61,
    ISMRMRD_IMAGE_USER6              = 62,
    ISMRMRD_IMAGE_USER7              = 63,
    ISMRMRD_IMAGE_USER8              = 64
};

/**
 * Struct used for keeping track of typical loop counters in MR experiment.
 */
typedef struct ISMRMRD_EncodingCounters {
    uint16_t kspace_encode_step_1;    /**< e.g. phase encoding line number */
    uint16_t kspace_encode_step_2;    /**< e.g. partition encoding number */
    uint16_t average;                 /**< e.g. signal average number */
    uint16_t slice;                   /**< e.g. imaging slice number */
    uint16_t contrast;                /**< e.g. echo number in multi-echo */
    uint16_t phase;                   /**< e.g. cardiac phase number */
    uint16_t repetition;              /**< e.g. dynamic number for dynamic scanning */
    uint16_t set;                     /**< e.g. flow encoding set */
    uint16_t segment;                 /**< e.g. segment number for segmented acquisition */
    uint16_t user[ISMRMRD_USER_INTS]; /**< Free user parameters */
} ISMRMRD_EncodingCounters;

/**
 * Header for each MR acquisition.
 */
typedef struct ISMRMRD_AcquisitionHeader {
    uint16_t version;                                    /**< First unsigned int indicates the version */
    uint64_t flags;                                      /**< bit field with flags */
    uint32_t measurement_uid;                            /**< Unique ID for the measurement */
    uint32_t scan_counter;                               /**< Current acquisition number in the measurement */
    uint32_t acquisition_time_stamp;                     /**< Acquisition clock */
    uint32_t physiology_time_stamp[ISMRMRD_PHYS_STAMPS]; /**< Physiology time stamps, e.g. ecg, breating, etc. */
    uint16_t number_of_samples;                          /**< Number of samples acquired */
    uint16_t available_channels;                         /**< Available coils */
    uint16_t active_channels;                            /**< Active coils on current acquisiton */
    uint64_t channel_mask[ISMRMRD_CHANNEL_MASKS];        /**< Mask to indicate which channels are active. Support for 1024 channels */
    uint16_t discard_pre;                                /**< Samples to be discarded at the beginning of  acquisition */
    uint16_t discard_post;                               /**< Samples to be discarded at the end of acquisition */
    uint16_t center_sample;                              /**< Sample at the center of k-space */
    uint16_t encoding_space_ref;                         /**< Reference to an encoding space, typically only one per acquisition */
    uint16_t trajectory_dimensions;                      /**< Indicates the dimensionality of the trajectory vector (0 means no trajectory) */
    float sample_time_us;                                /**< Time between samples in micro seconds, sampling BW */
    float position[3];                                   /**< Three-dimensional spatial offsets from isocenter */
    float read_dir[3];                                   /**< Directional cosines of the readout/frequency encoding */
    float phase_dir[3];                                  /**< Directional cosines of the phase */
    float slice_dir[3];                                  /**< Directional cosines of the slice direction */
    float patient_table_position[3];                     /**< Patient table off-center */
    ISMRMRD_EncodingCounters idx;                        /**< Encoding loop counters, see above */
    int32_t user_int[ISMRMRD_USER_INTS];                 /**< Free user parameters */
    float user_float[ISMRMRD_USER_FLOATS];               /**< Free user parameters */
} ISMRMRD_AcquisitionHeader;

/**
 * Initialize an Acquisition Header
 * @ingroup capi
 *
 */
EXPORTISMRMRD int ismrmrd_init_acquisition_header(ISMRMRD_AcquisitionHeader *hdr);

/** Individual MR acquisition. */
typedef struct ISMRMRD_Acquisition {
    ISMRMRD_AcquisitionHeader head; /**< Header, see above */
    float *traj;
    complex_float_t *data;
} ISMRMRD_Acquisition;

/** @addtogroup capi
 *  @{
 */
EXPORTISMRMRD ISMRMRD_Acquisition * ismrmrd_create_acquisition();
EXPORTISMRMRD int ismrmrd_free_acquisition(ISMRMRD_Acquisition *acq);
EXPORTISMRMRD int ismrmrd_init_acquisition(ISMRMRD_Acquisition *acq);
EXPORTISMRMRD int ismrmrd_cleanup_acquisition(ISMRMRD_Acquisition *acq);
EXPORTISMRMRD int ismrmrd_copy_acquisition(ISMRMRD_Acquisition *acqdest, const ISMRMRD_Acquisition *acqsource);
EXPORTISMRMRD int ismrmrd_make_consistent_acquisition(ISMRMRD_Acquisition *acq);
EXPORTISMRMRD size_t ismrmrd_size_of_acquisition_traj(const ISMRMRD_Acquisition *acq);
EXPORTISMRMRD size_t ismrmrd_size_of_acquisition_data(const ISMRMRD_Acquisition *acq);
/** @} */

/**********/
/* Images */
/**********/

/**
 *  Header for each Image
 */
typedef struct ISMRMRD_ImageHeader {
    uint16_t version;                                    /**< First unsigned int indicates the version */
    uint16_t data_type;                                  /**< e.g. unsigned short, float, complex float, etc. */
    uint64_t flags;                                      /**< bit field with flags */
    uint32_t measurement_uid;                            /**< Unique ID for the measurement  */
    uint16_t matrix_size[3];                             /**< Pixels in the 3 spatial dimensions */
    float field_of_view[3];                              /**< Size (in mm) of the 3 spatial dimensions */
    uint16_t channels;                                   /**< Number of receive channels */
    float position[3];                                   /**< Three-dimensional spatial offsets from isocenter */
    float read_dir[3];                                   /**< Directional cosines of the readout/frequency encoding */
    float phase_dir[3];                                  /**< Directional cosines of the phase */
    float slice_dir[3];                                  /**< Directional cosines of the slice direction */
    float patient_table_position[3];                     /**< Patient table off-center */
    uint16_t average;                                    /**< e.g. signal average number */
    uint16_t slice;                                      /**< e.g. imaging slice number */
    uint16_t contrast;                                   /**< e.g. echo number in multi-echo */
    uint16_t phase;                                      /**< e.g. cardiac phase number */
    uint16_t repetition;                                 /**< e.g. dynamic number for dynamic scanning */
    uint16_t set;                                        /**< e.g. flow encodning set */
    uint32_t acquisition_time_stamp;                     /**< Acquisition clock */
    uint32_t physiology_time_stamp[ISMRMRD_PHYS_STAMPS]; /**< Physiology time stamps, e.g. ecg, breathing, etc. */
    uint16_t image_type;                                 /**< e.g. magnitude, phase, complex, real, imag, etc. */
    uint16_t image_index;                                /**< e.g. image number in series of images  */
    uint16_t image_series_index;                         /**< e.g. series number */
    int32_t user_int[ISMRMRD_USER_INTS];                 /**< Free user parameters */
    float user_float[ISMRMRD_USER_FLOATS];               /**< Free user parameters */
    uint32_t attribute_string_len;                       /**< Length of attributes string */
} ISMRMRD_ImageHeader;

/** @ingroup capi */
EXPORTISMRMRD int ismrmrd_init_image_header(ISMRMRD_ImageHeader *hdr);

/**
 *  An individual Image
 *  @ingroup capi
 */
typedef struct ISMRMRD_Image {
    ISMRMRD_ImageHeader head;
    char *attribute_string;
    void *data;
} ISMRMRD_Image;


/** @addtogroup capi
 *  @{
 */
EXPORTISMRMRD ISMRMRD_Image * ismrmrd_create_image();
EXPORTISMRMRD int ismrmrd_free_image(ISMRMRD_Image *im);
EXPORTISMRMRD int ismrmrd_init_image(ISMRMRD_Image *im);
EXPORTISMRMRD int ismrmrd_cleanup_image(ISMRMRD_Image *im);
EXPORTISMRMRD int ismrmrd_copy_image(ISMRMRD_Image *imdest, const ISMRMRD_Image *imsource);
EXPORTISMRMRD int ismrmrd_make_consistent_image(ISMRMRD_Image *im);
EXPORTISMRMRD size_t ismrmrd_size_of_image_attribute_string(const ISMRMRD_Image *im);
EXPORTISMRMRD size_t ismrmrd_size_of_image_data(const ISMRMRD_Image *im);
/** @} */

/************/
/* NDArrays */
/************/

/**
 *  A simple N dimensional array
 */
typedef struct ISMRMRD_NDArray {
    uint16_t version;                      /**< First unsigned int indicates the version */
    uint16_t data_type;                    /**< e.g. unsigned short, float, complex float, etc. */
    uint16_t ndim;                         /**< Number of dimensions */
    size_t   dims[ISMRMRD_NDARRAY_MAXDIM]; /**< Dimensions */
    void     *data;                        /**< Pointer to data */
} ISMRMRD_NDArray;

/** @addtogroup capi
 *  @{
 */
EXPORTISMRMRD ISMRMRD_NDArray * ismrmrd_create_ndarray();
EXPORTISMRMRD int ismrmrd_free_ndarray(ISMRMRD_NDArray *arr);
EXPORTISMRMRD int ismrmrd_init_ndarray(ISMRMRD_NDArray *arr);
EXPORTISMRMRD int ismrmrd_cleanup_ndarray(ISMRMRD_NDArray *arr);
EXPORTISMRMRD int ismrmrd_copy_ndarray(ISMRMRD_NDArray *arrdest, const ISMRMRD_NDArray *arrsource);
EXPORTISMRMRD int ismrmrd_make_consistent_ndarray(ISMRMRD_NDArray *arr);
EXPORTISMRMRD size_t ismrmrd_size_of_ndarray_data(const ISMRMRD_NDArray *arr);
/** @} */

/*********/
/* Flags */
/*********/
/** @addtogroup capi
 *  @{
 */
EXPORTISMRMRD bool ismrmrd_is_flag_set(const uint64_t flags, const uint64_t val);
EXPORTISMRMRD int ismrmrd_set_flag(uint64_t *flags, const uint64_t val);
EXPORTISMRMRD int ismrmrd_clear_flag(uint64_t *flags, const uint64_t val);
EXPORTISMRMRD int ismrmrd_clear_all_flags(uint64_t *flags);
/** @} */

/** TODO: add helper functions for channel mask */

/******************/
/* Error Handling */
/******************/
/** @addtogroup capi
 *  @{
 */
typedef void (*ismrmrd_error_handler_t)(const char *file, int line,
        const char *function, int code, const char *msg);
#define ISMRMRD_PUSH_ERR(code, msg) ismrmrd_push_error(__FILE__, __LINE__, \
        __func__, (code), (msg))
int ismrmrd_push_error(const char *file, const int line, const char *func,
        const int code, const char *msg);
/** Sets a custom error handler */
EXPORTISMRMRD void ismrmrd_set_error_handler(ismrmrd_error_handler_t);
/** Returns message for corresponding error code */
EXPORTISMRMRD char *ismrmrd_strerror(int code);
/** @} */

/** Populates parameters (if non-NULL) with error information
 * @returns true if there was error information to return, false otherwise */
bool ismrmrd_pop_error(char **file, int *line, char **func,
        int *code, char **msg);

/*****************************/
/* Rotations and Quaternions */
/*****************************/
/** @addtogroup capi
 *  @{
 */
/** Calculates the determinant of the matrix and return the sign */
EXPORTISMRMRD int ismrmrd_sign_of_directions(float read_dir[3], float phase_dir[3], float slice_dir[3]);

/** Creates a normalized quaternion from a 3x3 rotation matrix */
EXPORTISMRMRD void ismrmrd_directions_to_quaternion(float read_dir[3], float phase_dir[3], float slice_dir[3], float quat[4]);

/** Converts a quaternion of the form | a b c d | to a 3x3 rotation matrix */
EXPORTISMRMRD void ismrmrd_quaternion_to_directions(float quat[4], float read_dir[3], float phase_dir[3], float slice_dir[3]);
/** @} */

#pragma pack(pop) // Restore old alignment

#ifdef __cplusplus
} // extern "C"

///  ISMRMRD C++ Interface

/// Some typedefs to beautify the namespace
typedef  ISMRMRD_EncodingCounters EncodingCounters;

/** @addtogroup cxxapi
 *  @{
 */

/// Convenience class for flags
class EXPORTISMRMRD FlagBit
{
public:
 FlagBit(unsigned short b)
   : bitmask_(0)
    {
      if (b > 0) {
    bitmask_ = 1;
    bitmask_ = (bitmask_ << (b-1));
      }
    }

  bool isSet(const uint64_t& m) const {
    return ((m & bitmask_)>0);
  }

  uint64_t bitmask_;

};

/// Header for MR Acquisition type
class EXPORTISMRMRD AcquisitionHeader: public ISMRMRD_AcquisitionHeader {
public:
    // Constructors
    AcquisitionHeader();

    // Flag methods
    bool isFlagSet(const ISMRMRD_AcquisitionFlags val);
    void setFlag(const ISMRMRD_AcquisitionFlags val);
    void clearFlag(const ISMRMRD_AcquisitionFlags val);
    void clearAllFlags();

    // Channel mask methods
    // TODO: need to add the functionality for these
    //bool isChannelActive(uint16_t channel_id);
    //void setChannelActive(uint16_t channel_id);
    //void setChannelNotActive(uint16_t channel_id);
    //void setAllChannelsNotActive();

};

/// MR Acquisition type
class EXPORTISMRMRD Acquisition: protected ISMRMRD_Acquisition {
public:
    // Constructors, assignment, destructor
    Acquisition();
    Acquisition(const Acquisition &other);
    Acquisition & operator= (const Acquisition &other);
    ~Acquisition();

    // Accessors and mutators
    const uint16_t &version();
    const uint64_t &flags();
    uint32_t &measurement_uid();
    uint32_t &scan_counter();
    uint32_t &acquisition_time_stamp();
    uint32_t (&physiology_time_stamp())[ISMRMRD_PHYS_STAMPS];
    const uint16_t &number_of_samples();
    void number_of_samples(uint16_t num_samples);
    uint16_t &available_channels();
    const uint16_t &active_channels();
    void active_channels(uint16_t num_active_channels);
    const uint64_t (&channel_mask())[ISMRMRD_CHANNEL_MASKS];
    uint16_t &discard_pre();
    uint16_t &discard_post();
    uint16_t &center_sample();
    uint16_t &encoding_space_ref();
    const uint16_t &trajectory_dimensions();
    void trajectory_dimensions(uint16_t traj_dim);
    float &sample_time_us();
    float (&position())[3];
    float (&read_dir())[3];
    float (&phase_dir())[3];
    float (&slice_dir())[3];
    float (&patient_table_position())[3];
    ISMRMRD_EncodingCounters &idx();
    int32_t (&user_int())[ISMRMRD_USER_INTS];
    float (&user_float())[ISMRMRD_USER_FLOATS];

    // Sizes
    const size_t getNumberOfDataElements();
    const size_t getNumberOfTrajElements();

    // Header, data and trajectory accessors
    AcquisitionHeader &getHead();
    void setHead(const AcquisitionHeader other);
    complex_float_t *getData();
    float *getTraj();

    // Flag methods
    bool isFlagSet(const uint64_t val);
    void setFlag(const uint64_t val);
    void clearFlag(const uint64_t val);
    void clearAllFlags();

    // Channel mask methods
    // TODO: need to add the functionality for these
    //bool isChannelActive(uint16_t channel_id);
    //void setChannelActive(uint16_t channel_id);
    //void setChannelNotActive(uint16_t channel_id);
    //void setAllChannelsNotActive();

};

/// Header for MR Image type
class EXPORTISMRMRD ImageHeader: public ISMRMRD_ImageHeader {
public:
    // Constructor
    ImageHeader();

    // Flag methods
    bool isFlagSet(const uint64_t val);
    void setFlag(const uint64_t val);
    void clearFlag(const uint64_t val);
    void clearAllFlags();

};

/// MR Image type
class EXPORTISMRMRD Image : protected ISMRMRD_Image {
public:
    // Constructors
    Image();
    Image(const Image &other);
    Image & operator= (const Image &other);
    ~Image();

    // Accessors and mutators
    const uint16_t &version();
    const uint16_t &data_type();
    void data_type(uint16_t dtype);
    const uint64_t &flags();
    uint32_t &measurement_uid();
    const uint16_t (&matrix_size())[3];
    void matrix_size(const uint16_t msize[3]);
    float (&field_of_view())[3];
    const uint16_t &channels();
    void channels(const uint16_t num_channels);
    float (&position())[3];
    float (&read_dir())[3];
    float (&phase_dir())[3];
    float (&slice_dir())[3];
    float (&patient_table_position())[3];
    uint16_t &average();
    uint16_t &slice();
    uint16_t &contrast();
    uint16_t &phase();
    uint16_t &repetition();
    uint16_t &set();
    uint32_t &acquisition_time_stamp();
    uint32_t (&physiology_time_stamp())[ISMRMRD_PHYS_STAMPS];
    uint16_t &image_type();
    uint16_t &image_index();
    uint16_t &image_series_index();
    int32_t (&user_int())[ISMRMRD_USER_INTS];
    float (&user_float())[ISMRMRD_USER_FLOATS];
    const uint32_t &attribute_string_len();

    // Header and data accessors
    ImageHeader &getHead();
    void setHead(const ImageHeader other);
    void getAttributeString(std::string &atrr);
    void setAttributeString(const std::string attr);
    void *getData();
    size_t getDataSize();

    // Flag methods
    bool isFlagSet(const uint64_t val);
    void setFlag(const uint64_t val);
    void clearFlag(const uint64_t val);
    void clearAllFlags();
};

/// N-Dimensional array type
template <typename T> class EXPORTISMRMRD NDArray: protected ISMRMRD_NDArray {
    friend class Dataset;
public:
    // Constructors, destructor and copy
    NDArray();
    NDArray(const std::vector<size_t> dimvec);
    NDArray(const NDArray<T> &other);
    ~NDArray();
    NDArray<T> & operator= (const NDArray<T> &other);

    // Accessors and mutators
    const uint16_t getVersion();
    const ISMRMRD_DataTypes getDataType();
    const uint16_t getNDim();
    const size_t (&getDims())[ISMRMRD_NDARRAY_MAXDIM];
    const size_t getDataSize();
    int resize(const std::vector<size_t> dimvec);
    const size_t getNumberOfElements();
    T * getData();

};


/** @} */

} // namespace ISMRMRD

#endif

#endif // ISMRMRD_H