#include <string.h>
#include <stdlib.h>

#include "ismrmrd.h"

namespace ISMRMRD {

//
// AcquisitionHeader class implementation
//
// Constructors
AcquisitionHeader::AcquisitionHeader() {
    ismrmrd_init_acquisition_header(this);
};

// Flag methods
bool AcquisitionHeader::isFlagSet(const ISMRMRD_AcquisitionFlags val) {
    return ismrmrd_is_flag_set(flags, val);
};

void AcquisitionHeader::setFlag(const ISMRMRD_AcquisitionFlags val) {
    ismrmrd_set_flag(&flags, val);
};

void AcquisitionHeader::clearFlag(const ISMRMRD_AcquisitionFlags val) {
    ismrmrd_clear_flag(&flags, val);
};

void AcquisitionHeader::clearAllFlags() {
    ismrmrd_clear_all_flags(&flags);
};

// TODO: Channel mask methods go here

//
// Acquisition class Implementation
//
// Constructors, assignment operator, destructor
Acquisition::Acquisition() {
    ismrmrd_init_acquisition(this);
}

Acquisition::Acquisition(const Acquisition &other) {
    // This is a deep copy
    ismrmrd_init_acquisition(this);
    ismrmrd_copy_acquisition(this, &other);
}

Acquisition::Acquisition(const ISMRMRD_Acquisition *acq) {
    // This is a deep copy
    ismrmrd_init_acquisition(this);
    ismrmrd_copy_acquisition(this, acq);
}

Acquisition & Acquisition::operator= (const Acquisition &other) {
    // Assignment makes a copy
    if (this != &other )
    {
        ismrmrd_init_acquisition(this);
        ismrmrd_copy_acquisition(this, &other);
    }
    return *this;
}

Acquisition::~Acquisition() {
    ismrmrd_cleanup_acquisition(this);
}

// Accessors and mutators
const uint16_t &Acquisition::version() {
    return head.version;
}

const uint64_t &Acquisition::flags() {
    return head.flags;
}

uint32_t &Acquisition::measurement_uid() {
    return head.measurement_uid;
}

uint32_t &Acquisition::scan_counter() {
    return head.scan_counter;
}

uint32_t &Acquisition::acquisition_time_stamp() {
    return head.acquisition_time_stamp;
}

uint32_t (&Acquisition::physiology_time_stamp()) [ISMRMRD_PHYS_STAMPS] {
    return head.physiology_time_stamp;
}

const uint16_t &Acquisition::number_of_samples() {
    return head.number_of_samples;
}

void Acquisition::number_of_samples(uint16_t num_samples) {
    head.number_of_samples = num_samples;
    ismrmrd_make_consistent_acquisition(this);
}

uint16_t &Acquisition::available_channels() {
    return head.available_channels;
}

const uint16_t &Acquisition::active_channels() {
    return head.active_channels;
}

void Acquisition::active_channels(uint16_t num_channels) {
    head.active_channels = num_channels;
    ismrmrd_make_consistent_acquisition(this);
}

const uint64_t (&Acquisition::channel_mask()) [ISMRMRD_CHANNEL_MASKS] {
    return head.channel_mask;
}

uint16_t &Acquisition::discard_pre() {
    return head.discard_pre;
}

uint16_t &Acquisition::discard_post() {
    return head.discard_post;
}

uint16_t &Acquisition::center_sample() {
    return head.center_sample;
}

uint16_t &Acquisition::encoding_space_ref() {
    return head.encoding_space_ref;
}

uint16_t &Acquisition::trajectory_dimensions() {
    return head.trajectory_dimensions;
}

float &Acquisition::sample_time_us() {
    return head.sample_time_us;
}

float (&Acquisition::position())[3] {
    return head.position;
}

float (&Acquisition::read_dir())[3] {
    return head.read_dir;
}

float (&Acquisition::phase_dir())[3] {
    return head.phase_dir;
}

float (&Acquisition::slice_dir())[3] {
    return head.slice_dir;
}

float (&Acquisition::patient_table_position())[3] {
    return head.patient_table_position;
}

ISMRMRD_EncodingCounters &Acquisition::idx() {
    return head.idx;
}

int32_t (&Acquisition::user_int()) [ISMRMRD_USER_INTS] {
    return head.user_int;
}

float (&Acquisition::user_float()) [ISMRMRD_USER_FLOATS] {
    return head.user_float;
}

// Data and Trajectory accessors
AcquisitionHeader & Acquisition::getHead() {
    // This returns a reference
    return *static_cast<AcquisitionHeader *>(&head);
}

void Acquisition::setHead(const AcquisitionHeader other) {
    memcpy(&head, &other, sizeof(AcquisitionHeader));
    ismrmrd_make_consistent_acquisition(this);
}

complex_float_t * Acquisition::getData() {
    return data;
}

float * Acquisition::getTraj() {
    return traj;
}

// Flag methods
bool Acquisition::isFlagSet(const uint64_t val) {
    return ismrmrd_is_flag_set(head.flags, val);
};
void Acquisition::setFlag(const uint64_t val) {
    ismrmrd_set_flag(&head.flags, val);
};
void Acquisition::clearFlag(const uint64_t val) {
    ismrmrd_clear_flag(&head.flags, val);
};
void Acquisition::clearAllFlags() {
    ismrmrd_clear_all_flags(&head.flags);
};

// TODO: Channel mask methods go here

//
// ImageHeader class Implementation
//

// Constructor
ImageHeader::ImageHeader() {
    ismrmrd_init_image_header(this);
};

// Flag methods
bool ImageHeader::isFlagSet(const uint64_t val) {
    return ismrmrd_is_flag_set(flags, val);
};

void ImageHeader::setFlag(const uint64_t val) {
    ismrmrd_set_flag(&flags, val);
};

void ImageHeader::clearFlag(const uint64_t val) {
    ismrmrd_clear_flag(&flags, val);
};

void ImageHeader::clearAllFlags() {
    ismrmrd_clear_all_flags(&flags);
};

//
// Image class Implementation
//

// Constructors
Image::Image() {
    ismrmrd_init_image(&image_);
};

// Accessors and mutators
const uint16_t &Image::version() {
    return image_.head.version;
};

const uint16_t &Image::data_type() {
    return image_.head.data_type;
};

void Image::data_type(uint16_t dtype) {
    // TODO function to check if type is valid
    image_.head.data_type = dtype;
    ismrmrd_make_consistent_image(&image_);
};

const uint64_t &Image::flags() {
    return image_.head.flags;
};

uint32_t &Image::measurement_uid() {
    return image_.head.measurement_uid;
};

const uint16_t (&Image::matrix_size())[3] {
    return image_.head.matrix_size;
};

void Image::matrix_size(const uint16_t msize[3]) {
    image_.head.matrix_size[0] = msize[0];
    if (msize[1] > 1) {
        image_.head.matrix_size[1] = msize[1];
    } else {
        image_.head.matrix_size[1] = 1;
    }
    if (msize[2] > 0) {
        image_.head.matrix_size[2] = msize[2];
    } else {
        image_.head.matrix_size[2] = 1;
    }
    ismrmrd_make_consistent_image(&image_);
};

float (&Image::field_of_view())[3] {
    return image_.head.field_of_view;
};

const uint16_t &Image::channels() {
    return image_.head.channels;
};

void Image::channels(const uint16_t num_channels) {
    if (num_channels > 1) {
        image_.head.channels = num_channels;
    } else {
        image_.head.channels = 1;
    }
    ismrmrd_make_consistent_image(&image_);
};

float (&Image::position())[3] {
    return image_.head.position;
};

float (&Image::read_dir())[3] {
    return image_.head.read_dir;
};

float (&Image::phase_dir())[3] {
    return image_.head.phase_dir;
};

float (&Image::slice_dir())[3] {
    return image_.head.slice_dir;
};

float (&Image::patient_table_position())[3] {
    return image_.head.patient_table_position;
};

uint16_t &Image::average() {
    return image_.head.average;
};

uint16_t &Image::slice() {
    return image_.head.slice;
};

uint16_t &Image::contrast() {
    return image_.head.contrast;
};

uint16_t &Image::phase() {
    return image_.head.repetition;
};

uint16_t &Image::repetition() {
    return image_.head.repetition;
};

uint16_t &Image::set() {
    return image_.head.set;
};

uint32_t &Image::acquisition_time_stamp() {
    return image_.head.acquisition_time_stamp;
};

uint32_t (&Image::physiology_time_stamp()) [ISMRMRD_PHYS_STAMPS] { 
    return image_.head.physiology_time_stamp;
};

uint16_t &Image::image_type() {
    return image_.head.image_type;
};

uint16_t &Image::image_index() {
    return image_.head.image_index;
};

uint16_t &Image::image_series_index() {
    return image_.head.image_series_index;
};

int32_t (&Image::user_int()) [ISMRMRD_USER_INTS] { 
    return image_.head.user_int;
};

float (&Image::user_float()) [ISMRMRD_USER_FLOATS] {
    return image_.head.user_float;
};

const uint32_t &Image::attribute_string_len() {
    return image_.head.attribute_string_len;
};

// Flag methods
bool Image::isFlagSet(const uint64_t val) {
    return ismrmrd_is_flag_set(image_.head.flags, val);
};

void Image::setFlag(const uint64_t val) {
    ismrmrd_set_flag(&(image_.head.flags), val);
};

void Image::clearFlag(const uint64_t val) {
    ismrmrd_clear_flag(&(image_.head.flags), val);
};

void Image::clearAllFlags() {
    ismrmrd_clear_all_flags(&(image_.head.flags));
};

//
// Array class Implementation
//
NDArray::NDArray()
{
    ismrmrd_init_ndarray(this);
}

NDArray::NDArray(const ISMRMRD_DataTypes dtype, const std::vector<uint16_t> dimvec)
{
    ismrmrd_init_ndarray(this);
    setProperties(dtype, dimvec);    
}

NDArray::NDArray(const NDArray &other)
{
    ismrmrd_init_ndarray(this);
    ismrmrd_copy_ndarray(this, &other);
}

NDArray::~NDArray()
{
    ismrmrd_cleanup_ndarray(this);
}

NDArray & NDArray::operator= (const NDArray &other)
{
    // Assignment makes a copy
    if (this != &other )
    {
        ismrmrd_init_ndarray(this);
        ismrmrd_copy_ndarray(this, &other);
    }
    return *this;
}

const uint16_t NDArray::getVersion() {
    return version;
};

const ISMRMRD_DataTypes NDArray::getDataType() {
    return static_cast<ISMRMRD_DataTypes>( data_type );
}

const uint16_t NDArray::getNDim() {
    return  ndim;
};
    
const uint16_t (&NDArray::getDims())[ISMRMRD_NDARRAY_MAXDIM] {
    return dims;
};

int NDArray::setProperties(const ISMRMRD_DataTypes dtype, const std::vector<uint16_t> dimvec) {
    if (dimvec.size() > ISMRMRD_NDARRAY_MAXDIM) {
        // TODO throw exception
        return ISMRMRD_MEMORYERROR;
    }
    data_type = dtype;
    ndim = dimvec.size();
    for (int n=0; n<ndim; n++) {
        dims[n] = dimvec[n];
    }
    int status=ismrmrd_make_consistent_ndarray(this);
    return status;
}

void * NDArray::getData() {
    return data;
}

} // namespace ISMRMRD