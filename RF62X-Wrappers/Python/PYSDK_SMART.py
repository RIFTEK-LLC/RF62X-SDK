import ctypes, os, sys
from ctypes import *
from struct import unpack
from socket import inet_aton
from enum import IntEnum
import platform
from threading import Lock

dll_name_no_ext="RF62X-SDK"

#####################################################
if platform.system()=='Windows':
    lib = cdll.LoadLibrary("./"+dll_name_no_ext+".dll")
elif platform.system()=='Linux':
    lib = cdll.LoadLibrary("./lib"+dll_name_no_ext+".so")
else:
    print("Unknown platform:", platform.system())
#####################################################

######################



import ctypes, os, sys
from ctypes import *

_int_types = (c_int16, c_int32)
if hasattr(ctypes, "c_int64"):
    # Some builds of ctypes apparently do not have c_int64
    # defined; it's a pretty good bet that these builds do not
    # have 64-bit pointers.
    _int_types += (c_int64,)
for t in _int_types:
    if sizeof(t) == sizeof(c_size_t):
        c_ptrdiff_t = t
del t
del _int_types


class UserString:
    def __init__(self, seq):
        if isinstance(seq, bytes):
            self.data = seq
        elif isinstance(seq, UserString):
            self.data = seq.data[:]
        else:
            self.data = str(seq).encode()

    def __bytes__(self):
        return self.data

    def __str__(self):
        return self.data.decode()

    def __repr__(self):
        return repr(self.data)

    def __int__(self):
        return int(self.data.decode())

    def __long__(self):
        return int(self.data.decode())

    def __float__(self):
        return float(self.data.decode())

    def __complex__(self):
        return complex(self.data.decode())

    def __hash__(self):
        return hash(self.data)

    def __cmp__(self, string):
        if isinstance(string, UserString):
            return cmp(self.data, string.data)
        else:
            return cmp(self.data, string)

    def __le__(self, string):
        if isinstance(string, UserString):
            return self.data <= string.data
        else:
            return self.data <= string

    def __lt__(self, string):
        if isinstance(string, UserString):
            return self.data < string.data
        else:
            return self.data < string

    def __ge__(self, string):
        if isinstance(string, UserString):
            return self.data >= string.data
        else:
            return self.data >= string

    def __gt__(self, string):
        if isinstance(string, UserString):
            return self.data > string.data
        else:
            return self.data > string

    def __eq__(self, string):
        if isinstance(string, UserString):
            return self.data == string.data
        else:
            return self.data == string

    def __ne__(self, string):
        if isinstance(string, UserString):
            return self.data != string.data
        else:
            return self.data != string

    def __contains__(self, char):
        return char in self.data

    def __len__(self):
        return len(self.data)

    def __getitem__(self, index):
        return self.__class__(self.data[index])

    def __getslice__(self, start, end):
        start = max(start, 0)
        end = max(end, 0)
        return self.__class__(self.data[start:end])

    def __add__(self, other):
        if isinstance(other, UserString):
            return self.__class__(self.data + other.data)
        elif isinstance(other, bytes):
            return self.__class__(self.data + other)
        else:
            return self.__class__(self.data + str(other).encode())

    def __radd__(self, other):
        if isinstance(other, bytes):
            return self.__class__(other + self.data)
        else:
            return self.__class__(str(other).encode() + self.data)

    def __mul__(self, n):
        return self.__class__(self.data * n)

    __rmul__ = __mul__

    def __mod__(self, args):
        return self.__class__(self.data % args)

    # the following methods are defined in alphabetical order:
    def capitalize(self):
        return self.__class__(self.data.capitalize())

    def center(self, width, *args):
        return self.__class__(self.data.center(width, *args))

    def count(self, sub, start=0, end=sys.maxsize):
        return self.data.count(sub, start, end)

    def decode(self, encoding=None, errors=None):  # XXX improve this?
        if encoding:
            if errors:
                return self.__class__(self.data.decode(encoding, errors))
            else:
                return self.__class__(self.data.decode(encoding))
        else:
            return self.__class__(self.data.decode())

    def encode(self, encoding=None, errors=None):  # XXX improve this?
        if encoding:
            if errors:
                return self.__class__(self.data.encode(encoding, errors))
            else:
                return self.__class__(self.data.encode(encoding))
        else:
            return self.__class__(self.data.encode())

    def endswith(self, suffix, start=0, end=sys.maxsize):
        return self.data.endswith(suffix, start, end)

    def expandtabs(self, tabsize=8):
        return self.__class__(self.data.expandtabs(tabsize))

    def find(self, sub, start=0, end=sys.maxsize):
        return self.data.find(sub, start, end)

    def index(self, sub, start=0, end=sys.maxsize):
        return self.data.index(sub, start, end)

    def isalpha(self):
        return self.data.isalpha()

    def isalnum(self):
        return self.data.isalnum()

    def isdecimal(self):
        return self.data.isdecimal()

    def isdigit(self):
        return self.data.isdigit()

    def islower(self):
        return self.data.islower()

    def isnumeric(self):
        return self.data.isnumeric()

    def isspace(self):
        return self.data.isspace()

    def istitle(self):
        return self.data.istitle()

    def isupper(self):
        return self.data.isupper()

    def join(self, seq):
        return self.data.join(seq)

    def ljust(self, width, *args):
        return self.__class__(self.data.ljust(width, *args))

    def lower(self):
        return self.__class__(self.data.lower())

    def lstrip(self, chars=None):
        return self.__class__(self.data.lstrip(chars))

    def partition(self, sep):
        return self.data.partition(sep)

    def replace(self, old, new, maxsplit=-1):
        return self.__class__(self.data.replace(old, new, maxsplit))

    def rfind(self, sub, start=0, end=sys.maxsize):
        return self.data.rfind(sub, start, end)

    def rindex(self, sub, start=0, end=sys.maxsize):
        return self.data.rindex(sub, start, end)

    def rjust(self, width, *args):
        return self.__class__(self.data.rjust(width, *args))

    def rpartition(self, sep):
        return self.data.rpartition(sep)

    def rstrip(self, chars=None):
        return self.__class__(self.data.rstrip(chars))

    def split(self, sep=None, maxsplit=-1):
        return self.data.split(sep, maxsplit)

    def rsplit(self, sep=None, maxsplit=-1):
        return self.data.rsplit(sep, maxsplit)

    def splitlines(self, keepends=0):
        return self.data.splitlines(keepends)

    def startswith(self, prefix, start=0, end=sys.maxsize):
        return self.data.startswith(prefix, start, end)

    def strip(self, chars=None):
        return self.__class__(self.data.strip(chars))

    def swapcase(self):
        return self.__class__(self.data.swapcase())

    def title(self):
        return self.__class__(self.data.title())

    def translate(self, *args):
        return self.__class__(self.data.translate(*args))

    def upper(self):
        return self.__class__(self.data.upper())

    def zfill(self, width):
        return self.__class__(self.data.zfill(width))


class MutableString(UserString):
    """mutable string objects

    Python strings are immutable objects.  This has the advantage, that
    strings may be used as dictionary keys.  If this property isn't needed
    and you insist on changing string values in place instead, you may cheat
    and use MutableString.

    But the purpose of this class is an educational one: to prevent
    people from inventing their own mutable string class derived
    from UserString and than forget thereby to remove (override) the
    __hash__ method inherited from UserString.  This would lead to
    errors that would be very hard to track down.

    A faster and better solution is to rewrite your program using lists."""

    def __init__(self, string=""):
        self.data = string

    def __hash__(self):
        raise TypeError("unhashable type (it is mutable)")

    def __setitem__(self, index, sub):
        if index < 0:
            index += len(self.data)
        if index < 0 or index >= len(self.data):
            raise IndexError
        self.data = self.data[:index] + sub + self.data[index + 1 :]

    def __delitem__(self, index):
        if index < 0:
            index += len(self.data)
        if index < 0 or index >= len(self.data):
            raise IndexError
        self.data = self.data[:index] + self.data[index + 1 :]

    def __setslice__(self, start, end, sub):
        start = max(start, 0)
        end = max(end, 0)
        if isinstance(sub, UserString):
            self.data = self.data[:start] + sub.data + self.data[end:]
        elif isinstance(sub, bytes):
            self.data = self.data[:start] + sub + self.data[end:]
        else:
            self.data = self.data[:start] + str(sub).encode() + self.data[end:]

    def __delslice__(self, start, end):
        start = max(start, 0)
        end = max(end, 0)
        self.data = self.data[:start] + self.data[end:]

    def immutable(self):
        return UserString(self.data)

    def __iadd__(self, other):
        if isinstance(other, UserString):
            self.data += other.data
        elif isinstance(other, bytes):
            self.data += other
        else:
            self.data += str(other).encode()
        return self

    def __imul__(self, n):
        self.data *= n
        return self


class String(MutableString, Union):

    _fields_ = [("raw", POINTER(c_char)), ("data", c_char_p)]

    def __init__(self, obj=""):
        if isinstance(obj, (bytes, UserString)):
            self.data = bytes(obj)
        else:
            self.raw = obj

    def __len__(self):
        return self.data and len(self.data) or 0

    def from_param(cls, obj):
        # Convert None or 0
        if obj is None or obj == 0:
            return cls(POINTER(c_char)())

        # Convert from String
        elif isinstance(obj, String):
            return obj

        # Convert from bytes
        elif isinstance(obj, bytes):
            return cls(obj)

        # Convert from str
        elif isinstance(obj, str):
            return cls(obj.encode())

        # Convert from c_char_p
        elif isinstance(obj, c_char_p):
            return obj

        # Convert from POINTER(c_char)
        elif isinstance(obj, POINTER(c_char)):
            return obj

        # Convert from raw pointer
        elif isinstance(obj, int):
            return cls(cast(obj, POINTER(c_char)))

        # Convert from c_char array
        elif isinstance(obj, c_char * len(obj)):
            return obj

        # Convert from object
        else:
            return String.from_param(obj._as_parameter_)

    from_param = classmethod(from_param)


def ReturnString(obj, func=None, arguments=None):
    return String.from_param(obj)


# typechecked, and will be converted to c_void_p.
def UNCHECKED(type):
    if hasattr(type, "_type_") and isinstance(type._type_, str) and type._type_ != "P":
        return type
    else:
        return c_void_p


# our own wrapper class
class _variadic_function(object):
    def __init__(self, func, restype, argtypes, errcheck):
        self.func = func
        self.func.restype = restype
        self.argtypes = argtypes
        if errcheck:
            self.func.errcheck = errcheck

    def _as_parameter_(self):
        # So we can pass this variadic function as a function pointer
        return self.func

    def __call__(self, *args):
        fixed_args = []
        i = 0
        for argtype in self.argtypes:
            # Typecheck what we can
            fixed_args.append(argtype.from_param(args[i]))
            i += 1
        return self.func(*fixed_args + list(args[i:]))


def ord_if_char(value):
    """
    Simple helper used for casts to simple builtin types:  if the argument is a
    string type, it will be converted to it's ordinal value.

    This function will raise an exception if the argument is string with more
    than one characters.
    """
    return ord(value) if (isinstance(value, bytes) or isinstance(value, str)) else value



rfInt8 = c_int8#	platform_types.h: 12

rfInt16 = c_int16#	platform_types.h: 13

rfInt32 = c_int32#	platform_types.h: 14

rfUint8 = c_uint8#	platform_types.h: 16

rfUint16 = c_uint16#	platform_types.h: 17

rfUint32 = c_uint32#	platform_types.h: 18

rfChar = c_char#	platform_types.h: 20

rfBool = c_uint8#	platform_types.h: 22

rfSize = c_size_t#	platform_types.h: 25

rfInt = c_int#	platform_types.h: 26

rfFloat = c_float#	platform_types.h: 27

rfDouble = c_double#	platform_types.h: 28

rfInt64 = c_int64#	platform_types.h: 32

rfUint64 = c_uint64#	platform_types.h: 33

#	rf62X_types.h: 15
class struct_anon_2(Structure):
    pass

struct_anon_2.__slots__ = [
    'version',
    'length',
    'validated',
    'reserved',
]
struct_anon_2._fields_ = [
    ('version', rfUint32),
    ('length', rfUint32),
    ('validated', rfUint8),
    ('reserved', rfUint8),
]

config_options_t = struct_anon_2#	rf62X_types.h: 15

#	rf62X_types.h: 20
class struct_anon_3(Structure):
    pass

struct_anon_3.__slots__ = [
    'device_id',
    'serial',
    'serial_of_pcb',
    'operating_time_h',
    'operating_time_m',
    'operating_time_s',
    'runtime_h',
    'runtime_m',
    'runtime_s',
    'startup_counter',
    'firmware_ver',
    'hardware_ver',
    'customer_id',
    'fpga_freq',
    'base_z',
    'range_z',
    'range_x_start',
    'range_x_end',
    'pixels_divider',
    'profiles_divider',
    'fsbl_version',
    'oem_device_name',
    'reserved',
]
struct_anon_3._fields_ = [
    ('device_id', rfUint16),
    ('serial', rfUint32),
    ('serial_of_pcb', rfUint32),
    ('operating_time_h', rfUint32),
    ('operating_time_m', rfUint8),
    ('operating_time_s', rfUint8),
    ('runtime_h', rfUint32),
    ('runtime_m', rfUint8),
    ('runtime_s', rfUint8),
    ('startup_counter', rfUint32),
    ('firmware_ver', rfUint32),
    ('hardware_ver', rfUint32),
    ('customer_id', rfUint32),
    ('fpga_freq', rfUint32),
    ('base_z', rfUint32),
    ('range_z', rfUint32),
    ('range_x_start', rfUint32),
    ('range_x_end', rfUint32),
    ('pixels_divider', rfUint16),
    ('profiles_divider', rfUint16),
    ('fsbl_version', rfUint32),
    ('oem_device_name', rfChar * int(16)),
    ('reserved', rfUint8 * int(76)),
]

#	rf62X_types.h: 66
class struct_anon_4(Structure):
    pass

struct_anon_4.__slots__ = [
    'addr',
    'value',
]
struct_anon_4._fields_ = [
    ('addr', rfUint16),
    ('value', rfUint16),
]

#	rf62X_types.h: 47
class struct_anon_5(Structure):
    pass

struct_anon_5.__slots__ = [
    'name',
    'width',
    'height',
    'pixel_clock',
    'black_odd_lines',
    'black_even_lines',
    'frame_cycle_const_part',
    'frame_cycle_per_line_part',
    'frame_rate_or_exposure',
    'min_exposure',
    'image_flipping',
    'max_exposure',
    'edr_point1_value',
    'edr_point2_value',
    'edr_point1_pos',
    'edr_point2_pos',
    'reserved',
    'init_regs',
]
struct_anon_5._fields_ = [
    ('name', rfChar * int(32)),
    ('width', rfUint16),
    ('height', rfUint16),
    ('pixel_clock', rfUint32),
    ('black_odd_lines', rfUint16),
    ('black_even_lines', rfUint16),
    ('frame_cycle_const_part', rfUint32),
    ('frame_cycle_per_line_part', rfUint32),
    ('frame_rate_or_exposure', rfUint8),
    ('min_exposure', rfUint32),
    ('image_flipping', rfUint8),
    ('max_exposure', rfUint32),
    ('edr_point1_value', rfUint8),
    ('edr_point2_value', rfUint8),
    ('edr_point1_pos', rfUint16),
    ('edr_point2_pos', rfUint16),
    ('reserved', rfUint8 * int(113)),
    ('init_regs', struct_anon_4 * int(64)),
]

#	rf62X_types.h: 73
class struct_anon_6(Structure):
    pass

struct_anon_6.__slots__ = [
    'mac',
    'eip_vendor_id',
    'eip_device_type',
    'force_autoneg_time',
    'reserved',
]
struct_anon_6._fields_ = [
    ('mac', rfUint8 * int(6)),
    ('eip_vendor_id', rfUint16),
    ('eip_device_type', rfUint16),
    ('force_autoneg_time', rfUint8),
    ('reserved', rfUint8 * int(31)),
]

#	rf62X_types.h: 82
class struct_anon_7(Structure):
    pass

struct_anon_7.__slots__ = [
    'wave_length',
    'koeff1',
    'koeff2',
    'min_value',
    'max_value',
    'enable_mode_change',
    'reserved',
]
struct_anon_7._fields_ = [
    ('wave_length', rfUint16),
    ('koeff1', rfUint8),
    ('koeff2', rfUint8),
    ('min_value', rfUint32),
    ('max_value', rfUint32),
    ('enable_mode_change', rfUint8),
    ('reserved', rfUint8 * int(31)),
]

#	rf62X_types.h: 93
class struct_anon_8(Structure):
    pass

struct_anon_8.__slots__ = [
    'in1_min_delay',
    'in1_max_delay',
    'max_divider_in1',
    'min_divider_in1',
    'reserved',
]
struct_anon_8._fields_ = [
    ('in1_min_delay', rfUint16),
    ('in1_max_delay', rfUint32),
    ('max_divider_in1', rfUint16),
    ('min_divider_in1', rfUint16),
    ('reserved', rfUint8 * int(62)),
]

#	rf62X_types.h: 102
class struct_anon_9(Structure):
    pass

struct_anon_9.__slots__ = [
    'out1_min_delay',
    'out1_max_delay',
    'out1_min_pulse_width',
    'out1_max_pulse_width',
    'out2_min_delay',
    'out2_max_delay',
    'out2_min_pulse_width',
    'out2_max_pulse_width',
    'reserved',
]
struct_anon_9._fields_ = [
    ('out1_min_delay', rfUint16),
    ('out1_max_delay', rfUint32),
    ('out1_min_pulse_width', rfUint16),
    ('out1_max_pulse_width', rfUint32),
    ('out2_min_delay', rfUint16),
    ('out2_max_delay', rfUint32),
    ('out2_min_pulse_width', rfUint16),
    ('out2_max_pulse_width', rfUint32),
    ('reserved', rfUint8 * int(32)),
]

#	rf62X_types.h: 115
class struct_anon_10(Structure):
    pass

struct_anon_10.__slots__ = [
    'max_dump_size',
    'reserved',
]
struct_anon_10._fields_ = [
    ('max_dump_size', rfUint32),
    ('reserved', rfUint8 * int(60)),
]

#	rf62X_types.h: 128
class struct_anon_11(Structure):
    pass

struct_anon_11.__slots__ = [
    'major_rev',
    'minor_rev',
]
struct_anon_11._fields_ = [
    ('major_rev', c_uint8),
    ('minor_rev', rfUint8),
]

#	rf62X_types.h: 123
class struct_anon_12(Structure):
    pass

struct_anon_12.__slots__ = [
    'vendor_iD',
    'device_type',
    'product_code',
    'revision',
]
struct_anon_12._fields_ = [
    ('vendor_iD', rfUint16),
    ('device_type', rfUint16),
    ('product_code', rfUint16),
    ('revision', struct_anon_11),
]

#	rf62X_types.h: 137
class struct_anon_13(Structure):
    pass

struct_anon_13.__slots__ = [
    'path_size',
    'classId',
    'instance_number',
    'attribute_number',
]
struct_anon_13._fields_ = [
    ('path_size', c_uint16),
    ('classId', rfUint16),
    ('instance_number', rfUint16),
    ('attribute_number', rfUint16),
]

#	rf62X_types.h: 134
class struct_anon_14(Structure):
    pass

struct_anon_14.__slots__ = [
    'config_capability',
    'phyLinkObject',
]
struct_anon_14._fields_ = [
    ('config_capability', rfUint32),
    ('phyLinkObject', struct_anon_13),
]

#	rf62X_types.h: 149
class struct_anon_15(Structure):
    pass

struct_anon_15.__slots__ = [
    'speed',
    'duplex',
]
struct_anon_15._fields_ = [
    ('speed', rfUint16),
    ('duplex', rfUint8),
]

#	rf62X_types.h: 146
class struct_anon_16(Structure):
    pass

struct_anon_16.__slots__ = [
    'capability_bits',
    'speed_dup_count',
    'speedDuplex',
]
struct_anon_16._fields_ = [
    ('capability_bits', c_uint16),
    ('speed_dup_count', rfUint8),
    ('speedDuplex', struct_anon_15 * int(4)),
]

#	rf62X_types.h: 121
class struct_anon_17(Structure):
    pass

struct_anon_17.__slots__ = [
    'identity',
    'tcpInterface',
    'intrf_type',
    'intrfCapability',
    'reserved',
]
struct_anon_17._fields_ = [
    ('identity', struct_anon_12),
    ('tcpInterface', struct_anon_14),
    ('intrf_type', rfUint8),
    ('intrfCapability', struct_anon_16),
    ('reserved', rfUint8 * int(44)),
]

#	rf62X_types.h: 161
class struct_anon_18(Structure):
    pass

struct_anon_18.__slots__ = [
    'general',
    'sensor',
    'network',
    'laser',
    'inputs',
    'outputs',
    'profiles',
    'eip',
    'reserved',
]
struct_anon_18._fields_ = [
    ('general', struct_anon_3),
    ('sensor', struct_anon_5),
    ('network', struct_anon_6),
    ('laser', struct_anon_7),
    ('inputs', struct_anon_8),
    ('outputs', struct_anon_9),
    ('profiles', struct_anon_10),
    ('eip', struct_anon_17),
    ('reserved', rfUint8 * int(167)),
]

rf627_old_factory_params_t = struct_anon_18#	rf62X_types.h: 161

#	rf62X_types.h: 169
class struct_anon_19(Structure):
    pass

struct_anon_19.__slots__ = [
    'Day',
    'Month',
    'Year',
]
struct_anon_19._fields_ = [
    ('Day', rfUint8),
    ('Month', rfUint8),
    ('Year', rfUint16),
]

#	rf62X_types.h: 175
class struct_anon_20(Structure):
    pass

struct_anon_20.__slots__ = [
    'Hour',
    'Minute',
    'Second',
]
struct_anon_20._fields_ = [
    ('Hour', rfUint8),
    ('Minute', rfUint8),
    ('Second', rfUint8),
]

#	rf62X_types.h: 167
class struct_anon_21(Structure):
    pass

struct_anon_21.__slots__ = [
    'date',
    'time',
]
struct_anon_21._fields_ = [
    ('date', struct_anon_19),
    ('time', struct_anon_20),
]

#	rf62X_types.h: 204
class struct_anon_22(Structure):
    pass

struct_anon_22.__slots__ = [
    'Tag',
    'FormatVersion',
    'timestamp',
    'DevType',
    'SerialNumber',
    'BaseZ',
    'RangeZ',
    'RangeXStart',
    'RangeXEnd',
    'YSteps',
    'StartPosition',
    'EndPosition',
    'CutXLeft',
    'CutXRight',
    'PlaneType',
    'InvertZ',
    'TriangleWidth',
    'TriangleHeight',
    'AveragingSize',
    'Exposure',
    'Temp',
    'StepLength',
    'FirmwareVer',
    'HardwareVer',
    'Reserved',
]
struct_anon_22._fields_ = [
    ('Tag', rfChar * int(4)),
    ('FormatVersion', rfUint16),
    ('timestamp', struct_anon_21),
    ('DevType', rfUint16),
    ('SerialNumber', rfUint32),
    ('BaseZ', rfUint16),
    ('RangeZ', rfUint16),
    ('RangeXStart', rfUint16),
    ('RangeXEnd', rfUint16),
    ('YSteps', rfUint16),
    ('StartPosition', rfUint16),
    ('EndPosition', rfUint16),
    ('CutXLeft', rfUint16),
    ('CutXRight', rfUint16),
    ('PlaneType', rfUint8),
    ('InvertZ', rfUint8),
    ('TriangleWidth', rfUint32),
    ('TriangleHeight', rfUint32),
    ('AveragingSize', rfUint8),
    ('Exposure', rfUint32),
    ('Temp', rfInt16),
    ('StepLength', rfDouble),
    ('FirmwareVer', rfUint32),
    ('HardwareVer', rfUint32),
    ('Reserved', rfUint8 * int(186)),
]

DTF_header = struct_anon_22#	rf62X_types.h: 204

#	rf62X_types.h: 213
class struct_anon_23(Structure):
    pass

struct_anon_23.__slots__ = [
    'Year',
    'Month',
    'Day',
]
struct_anon_23._fields_ = [
    ('Year', rfUint16),
    ('Month', rfUint8),
    ('Day', rfUint8),
]

#	rf62X_types.h: 219
class struct_anon_24(Structure):
    pass

struct_anon_24.__slots__ = [
    'Hour',
    'Minute',
    'Second',
]
struct_anon_24._fields_ = [
    ('Hour', rfUint8),
    ('Minute', rfUint8),
    ('Second', rfUint8),
]

#	rf62X_types.h: 211
class struct_anon_25(Structure):
    pass

struct_anon_25.__slots__ = [
    'date',
    'time',
]
struct_anon_25._fields_ = [
    ('date', struct_anon_23),
    ('time', struct_anon_24),
]

#	rf62X_types.h: 227
class struct_anon_26(Structure):
    pass

struct_anon_26.__slots__ = [
    'FormatVersion',
    'CRC',
    'SerialNumber',
    'timestamp',
    'Zero',
]
struct_anon_26._fields_ = [
    ('FormatVersion', rfUint8),
    ('CRC', rfUint16),
    ('SerialNumber', rfUint32),
    ('timestamp', struct_anon_25),
    ('Zero', rfUint8 * int(242)),
]

TBL_header = struct_anon_26#	rf62X_types.h: 227

#	rf62X_types.h: 231
class struct_anon_27(Structure):
    pass

struct_anon_27.__slots__ = [
    'name',
    'save_log_to_spi',
    'reserved',
]
struct_anon_27._fields_ = [
    ('name', rfChar * int(64)),
    ('save_log_to_spi', rfUint8),
    ('reserved', rfUint8 * int(127)),
]

#	rf62X_types.h: 238
class struct_anon_28(Structure):
    pass

struct_anon_28.__slots__ = [
    'fpga_temp',
    'params_changed',
    'sens00_temp',
    'sens00_max',
    'sens00_min',
    'sens01_temp',
    'sens01_max',
    'sens01_min',
    'sens10_temp',
    'sens10_max',
    'sens10_min',
    'sens11_temp',
    'sens11_max',
    'sens11_min',
    'reserved',
]
struct_anon_28._fields_ = [
    ('fpga_temp', rfInt16),
    ('params_changed', rfUint8),
    ('sens00_temp', rfInt16),
    ('sens00_max', rfInt16),
    ('sens00_min', rfInt16),
    ('sens01_temp', rfInt16),
    ('sens01_max', rfInt16),
    ('sens01_min', rfInt16),
    ('sens10_temp', rfInt16),
    ('sens10_max', rfInt16),
    ('sens10_min', rfInt16),
    ('sens11_temp', rfInt16),
    ('sens11_max', rfInt16),
    ('sens11_min', rfInt16),
    ('reserved', rfUint8 * int(55)),
]

#	rf62X_types.h: 257
class struct_anon_29(Structure):
    pass

struct_anon_29.__slots__ = [
    'enable',
    'tcp_port',
    'reserved',
]
struct_anon_29._fields_ = [
    ('enable', rfUint8),
    ('tcp_port', rfUint16),
    ('reserved', rfUint8 * int(32)),
]

#	rf62X_types.h: 264
class struct_anon_30(Structure):
    pass

struct_anon_30.__slots__ = [
    'dhs',
    'gain_analog',
    'gain_digital',
    'exposure',
    'max_exposure',
    'frame_rate',
    'max_frame_rate',
    'exposure_hdr_mode',
    'auto_exposure',
    'column_edr_mode',
    'column_exposure_div',
    'column_exposure_max_div',
    'reserved_1',
]
struct_anon_30._fields_ = [
    ('dhs', rfUint8),
    ('gain_analog', rfUint8),
    ('gain_digital', rfUint8),
    ('exposure', rfUint32),
    ('max_exposure', rfUint32),
    ('frame_rate', rfUint32),
    ('max_frame_rate', rfUint32),
    ('exposure_hdr_mode', rfUint8),
    ('auto_exposure', rfUint8),
    ('column_edr_mode', rfUint8),
    ('column_exposure_div', rfUint8),
    ('column_exposure_max_div', rfUint8),
    ('reserved_1', rfUint8 * int(59)),
]

#	rf62X_types.h: 281
class struct_anon_31(Structure):
    pass

struct_anon_31.__slots__ = [
    'enable',
    'active',
    'size',
    'position_mode',
    'manual_position',
    'auto_position',
    'required_profile_size',
    'reserved',
]
struct_anon_31._fields_ = [
    ('enable', rfUint8),
    ('active', rfUint8),
    ('size', rfUint16),
    ('position_mode', rfUint8),
    ('manual_position', rfUint16),
    ('auto_position', rfUint16),
    ('required_profile_size', rfUint16),
    ('reserved', rfUint8 * int(80)),
]

#	rf62X_types.h: 293
class struct_anon_32(Structure):
    pass

struct_anon_32.__slots__ = [
    'speed',
    'autonegotiation',
    'ip_address',
    'net_mask',
    'gateway_ip',
    'host_ip',
    'stream_port',
    'http_port',
    'service_port',
    'reserved',
]
struct_anon_32._fields_ = [
    ('speed', rfUint16),
    ('autonegotiation', rfUint8),
    ('ip_address', rfUint8 * int(4)),
    ('net_mask', rfUint8 * int(4)),
    ('gateway_ip', rfUint8 * int(4)),
    ('host_ip', rfUint8 * int(4)),
    ('stream_port', rfUint16),
    ('http_port', rfUint16),
    ('service_port', rfUint16),
    ('reserved', rfUint8 * int(68)),
]

#	rf62X_types.h: 309
class struct_anon_33(Structure):
    pass

struct_anon_33.__slots__ = [
    'enable',
    'format',
    'ack',
    'include_intensivity',
    'reserved',
]
struct_anon_33._fields_ = [
    ('enable', rfUint8),
    ('format', rfUint8),
    ('ack', rfUint8),
    ('include_intensivity', rfUint8),
    ('reserved', rfUint8 * int(31)),
]

#	rf62X_types.h: 318
class struct_anon_34(Structure):
    pass

struct_anon_34.__slots__ = [
    'brightness_threshold',
    'filter_width',
    'processing_mode',
    'reduce_noise',
    'frame_rate',
    'median_filter_mode',
    'bilateral_filter_mode',
    'peak_select_mode',
    'profile_flip',
    'reserved',
]
struct_anon_34._fields_ = [
    ('brightness_threshold', rfUint32),
    ('filter_width', rfUint8),
    ('processing_mode', rfUint8),
    ('reduce_noise', rfUint8),
    ('frame_rate', rfUint32),
    ('median_filter_mode', rfUint8),
    ('bilateral_filter_mode', rfUint8),
    ('peak_select_mode', rfUint8),
    ('profile_flip', rfUint8),
    ('reserved', rfUint8 * int(56)),
]

#	rf62X_types.h: 332
class struct_anon_35(Structure):
    pass

struct_anon_35.__slots__ = [
    'enable',
    'level_mode',
    'level',
    'reserved',
]
struct_anon_35._fields_ = [
    ('enable', rfUint8),
    ('level_mode', rfUint8),
    ('level', rfUint16),
    ('reserved', rfUint8 * int(32)),
]

#	rf62X_types.h: 343
class struct_anon_36(Structure):
    pass

struct_anon_36.__slots__ = [
    'params_mask',
    'in1_enable',
    'in1_mode',
    'in1_delay',
    'in1_decimation',
    'in2_enable',
    'in2_mode',
    'in2_invert',
    'in3_enable',
    'in3_mode',
    'reserved',
]
struct_anon_36._fields_ = [
    ('params_mask', rfUint16),
    ('in1_enable', rfUint8),
    ('in1_mode', rfUint8),
    ('in1_delay', rfUint32),
    ('in1_decimation', rfUint8),
    ('in2_enable', rfUint8),
    ('in2_mode', rfUint8),
    ('in2_invert', rfUint8),
    ('in3_enable', rfUint8),
    ('in3_mode', rfUint8),
    ('reserved', rfUint8 * int(12)),
]

#	rf62X_types.h: 340
class struct_anon_37(Structure):
    pass

struct_anon_37.__slots__ = [
    'preset_index',
    'params',
    'reserved',
]
struct_anon_37._fields_ = [
    ('preset_index', rfUint8),
    ('params', struct_anon_36 * int(12)),
    ('reserved', rfUint8 * int(32)),
]

#	rf62X_types.h: 360
class struct_anon_38(Structure):
    pass

struct_anon_38.__slots__ = [
    'out1_enable',
    'out1_mode',
    'out1_delay',
    'out1_pulse_width',
    'out1_invert',
    'out2_enable',
    'out2_mode',
    'out2_delay',
    'out2_pulse_width',
    'out2_invert',
    'reserved',
]
struct_anon_38._fields_ = [
    ('out1_enable', rfUint8),
    ('out1_mode', rfUint8),
    ('out1_delay', rfUint32),
    ('out1_pulse_width', rfUint32),
    ('out1_invert', rfUint8),
    ('out2_enable', rfUint8),
    ('out2_mode', rfUint8),
    ('out2_delay', rfUint32),
    ('out2_pulse_width', rfUint32),
    ('out2_invert', rfUint8),
    ('reserved', rfUint8 * int(32)),
]

#	rf62X_types.h: 376
class struct_anon_39(Structure):
    pass

struct_anon_39.__slots__ = [
    'general',
    'sysmon',
    'rf625compat',
    'sensor',
    'roi',
    'network',
    'stream',
    'image_processing',
    'laser',
    'inputs',
    'outputs',
    'reserved',
]
struct_anon_39._fields_ = [
    ('general', struct_anon_27),
    ('sysmon', struct_anon_28),
    ('rf625compat', struct_anon_29),
    ('sensor', struct_anon_30),
    ('roi', struct_anon_31),
    ('network', struct_anon_32),
    ('stream', struct_anon_33),
    ('image_processing', struct_anon_34),
    ('laser', struct_anon_35),
    ('inputs', struct_anon_37),
    ('outputs', struct_anon_38),
    ('reserved', rfUint8 * int(283)),
]

rf627_old_user_params_t = struct_anon_39#	rf62X_types.h: 376

#	rf62X_types.h: 406
class struct_anon_40(Structure):
    pass

struct_anon_40.__slots__ = [
    'data_type',
    'flags',
    'device_type',
    'serial_number',
    'system_time',
    'proto_version_major',
    'proto_version_minor',
    'hardware_params_offset',
    'data_offset',
    'packet_count',
    'measure_count',
    'zmr',
    'xemr',
    'discrete_value',
    'reserved_0',
    'license_hash',
    'exposure_time',
    'laser_value',
    'step_count',
    'dir',
    'payload_size',
    'bytes_per_point',
]
struct_anon_40._fields_ = [
    ('data_type', rfUint8),
    ('flags', rfUint8),
    ('device_type', rfUint16),
    ('serial_number', rfUint32),
    ('system_time', rfUint64),
    ('proto_version_major', rfUint8),
    ('proto_version_minor', rfUint8),
    ('hardware_params_offset', rfUint8),
    ('data_offset', rfUint8),
    ('packet_count', rfUint32),
    ('measure_count', rfUint32),
    ('zmr', rfUint16),
    ('xemr', rfUint16),
    ('discrete_value', rfUint16),
    ('reserved_0', rfUint8 * int(10)),
    ('license_hash', rfUint32),
    ('exposure_time', rfUint32),
    ('laser_value', rfUint32),
    ('step_count', rfUint32),
    ('dir', rfUint8),
    ('payload_size', rfUint16),
    ('bytes_per_point', rfUint8),
]

rf627_old_profile_header_t = struct_anon_40#	rf62X_types.h: 406

#	rf62X_types.h: 409
class struct_anon_41(Structure):
    pass

struct_anon_41.__slots__ = [
    'H',
    'M',
    'S',
]
struct_anon_41._fields_ = [
    ('H', rfUint32),
    ('M', rfUint8),
    ('S', rfUint8),
]

#	rf62X_types.h: 417
class struct_anon_42(Structure):
    pass

struct_anon_42.__slots__ = [
    'Time',
    'ModuleID',
    'EventID',
    'String',
]
struct_anon_42._fields_ = [
    ('Time', struct_anon_41),
    ('ModuleID', rfUint8),
    ('EventID', rfUint8),
    ('String', rfChar * int(128)),
]

log_record_t = struct_anon_42#	rf62X_types.h: 417

enum_anon_43 = c_int#	rf62X_types.h: 425

DTY_PixelsNormal = 16#	rf62X_types.h: 425

DTY_ProfileNormal = 17#	rf62X_types.h: 425

DTY_PixelsInterpolated = 18#	rf62X_types.h: 425

DTY_ProfileInterpolated = 19#	rf62X_types.h: 425

rf627_old_data_type_t = enum_anon_43#	rf62X_types.h: 425

#	rf62X_types.h: 433
class struct_anon_44(Structure):
    pass

struct_anon_44.__slots__ = [
    'x',
    'z',
]
struct_anon_44._fields_ = [
    ('x', rfFloat),
    ('z', rfFloat),
]

rf627_old_point2D_t = struct_anon_44#	rf62X_types.h: 433

#	rf62X_types.h: 442
class struct_anon_45(Structure):
    pass

struct_anon_45.__slots__ = [
    'x',
    'y',
    'z',
]
struct_anon_45._fields_ = [
    ('x', rfFloat),
    ('y', rfFloat),
    ('z', rfFloat),
]

rf627_old_point3D_t = struct_anon_45#	rf62X_types.h: 442

#	rf62X_types.h: 450
class struct_anon_46(Structure):
    pass

struct_anon_46.__slots__ = [
    'pixels',
    'pixels_count',
]
struct_anon_46._fields_ = [
    ('pixels', POINTER(rfUint16)),
    ('pixels_count', rfUint32),
]

#	rf62X_types.h: 454
class struct_anon_47(Structure):
    pass

struct_anon_47.__slots__ = [
    'points',
    'points_count',
]
struct_anon_47._fields_ = [
    ('points', POINTER(rf627_old_point2D_t)),
    ('points_count', rfUint32),
]

#	rf62X_types.h: 449
class union_anon_48(Union):
    pass

union_anon_48.__slots__ = [
    'pixels_format',
    'profile_format',
]
union_anon_48._fields_ = [
    ('pixels_format', struct_anon_46),
    ('profile_format', struct_anon_47),
]

#	rf62X_types.h: 461
class struct_anon_49(Structure):
    pass

struct_anon_49.__slots__ = [
    'header',
    'unnamed_1',
    'intensity',
    'intensity_count',
]
struct_anon_49._anonymous_ = [
    'unnamed_1',
]
struct_anon_49._fields_ = [
    ('header', rf627_old_profile_header_t),
    ('unnamed_1', union_anon_48),
    ('intensity', POINTER(rfUint8)),
    ('intensity_count', rfUint32),
]

rf627_old_profile2D_t = struct_anon_49#	rf62X_types.h: 461

#	rf62X_types.h: 469
class struct_anon_50(Structure):
    pass

struct_anon_50.__slots__ = [
    'pixels',
    'pixels_count',
]
struct_anon_50._fields_ = [
    ('pixels', POINTER(rfUint16)),
    ('pixels_count', rfUint32),
]

#	rf62X_types.h: 473
class struct_anon_51(Structure):
    pass

struct_anon_51.__slots__ = [
    'points',
    'points_count',
]
struct_anon_51._fields_ = [
    ('points', POINTER(rf627_old_point3D_t)),
    ('points_count', rfUint32),
]

#	rf62X_types.h: 468
class union_anon_52(Union):
    pass

union_anon_52.__slots__ = [
    'pixels_format',
    'profile_format',
]
union_anon_52._fields_ = [
    ('pixels_format', struct_anon_50),
    ('profile_format', struct_anon_51),
]

#	rf62X_types.h: 480
class struct_anon_53(Structure):
    pass

struct_anon_53.__slots__ = [
    'header',
    'unnamed_1',
    'intensity',
    'intensity_count',
]
struct_anon_53._anonymous_ = [
    'unnamed_1',
]
struct_anon_53._fields_ = [
    ('header', rf627_old_profile_header_t),
    ('unnamed_1', union_anon_52),
    ('intensity', POINTER(rfUint8)),
    ('intensity_count', rfUint32),
]

rf627_old_profile3D_t = struct_anon_53#	rf62X_types.h: 480

#	rf62X_types.h: 495
class struct_anon_54(Structure):
    pass

struct_anon_54.__slots__ = [
    'data',
    'data_size',
    'width',
    'height',
    'pixel_size',
    'user_roi_active',
    'user_roi_enabled',
    'user_roi_pos',
    'user_roi_size',
]
struct_anon_54._fields_ = [
    ('data', c_char_p),
    ('data_size', rfUint32),
    ('width', rfUint32),
    ('height', rfUint32),
    ('pixel_size', rfUint8),
    ('user_roi_active', rfBool),
    ('user_roi_enabled', rfBool),
    ('user_roi_pos', rfUint32),
    ('user_roi_size', rfUint32),
]

rf627_old_frame_t = struct_anon_54#	rf62X_types.h: 495

#	rf62X_types.h: 500
class struct_anon_55(Structure):
    pass

struct_anon_55.__slots__ = [
    'data',
]
struct_anon_55._fields_ = [
    ('data', c_char_p),
]

rf627_old_calib_table_t = struct_anon_55#	rf62X_types.h: 500

#	rf62X_types.h: 508
class struct_anon_56(Structure):
    pass

struct_anon_56.__slots__ = [
    'pixels',
    'pixels_count',
]
struct_anon_56._fields_ = [
    ('pixels', POINTER(rfUint16)),
    ('pixels_count', rfUint32),
]

#	rf62X_types.h: 512
class struct_anon_57(Structure):
    pass

struct_anon_57.__slots__ = [
    'points',
    'points_count',
]
struct_anon_57._fields_ = [
    ('points', POINTER(rf627_old_point2D_t)),
    ('points_count', rfUint32),
]

#	rf62X_types.h: 507
class union_anon_58(Union):
    pass

union_anon_58.__slots__ = [
    'pixels_format',
    'profile_format',
]
union_anon_58._fields_ = [
    ('pixels_format', struct_anon_56),
    ('profile_format', struct_anon_57),
]

#	rf62X_types.h: 519
class struct_anon_59(Structure):
    pass

struct_anon_59.__slots__ = [
    'header',
    'unnamed_1',
    'intensity',
    'intensity_count',
]
struct_anon_59._anonymous_ = [
    'unnamed_1',
]
struct_anon_59._fields_ = [
    ('header', rf627_old_profile_header_t),
    ('unnamed_1', union_anon_58),
    ('intensity', POINTER(rfUint8)),
    ('intensity_count', rfUint32),
]

rf627_smart_profile2D_t = struct_anon_59#	rf62X_types.h: 519

#	rf62X_types.h: 527
class struct_anon_60(Structure):
    pass

struct_anon_60.__slots__ = [
    'pixels',
    'pixels_count',
]
struct_anon_60._fields_ = [
    ('pixels', POINTER(rfUint16)),
    ('pixels_count', rfUint32),
]

#	rf62X_types.h: 531
class struct_anon_61(Structure):
    pass

struct_anon_61.__slots__ = [
    'points',
    'points_count',
]
struct_anon_61._fields_ = [
    ('points', POINTER(rf627_old_point3D_t)),
    ('points_count', rfUint32),
]

#	rf62X_types.h: 526
class union_anon_62(Union):
    pass

union_anon_62.__slots__ = [
    'pixels_format',
    'profile_format',
]
union_anon_62._fields_ = [
    ('pixels_format', struct_anon_60),
    ('profile_format', struct_anon_61),
]

#	rf62X_types.h: 538
class struct_anon_63(Structure):
    pass

struct_anon_63.__slots__ = [
    'header',
    'unnamed_1',
    'intensity',
    'intensity_count',
]
struct_anon_63._anonymous_ = [
    'unnamed_1',
]
struct_anon_63._fields_ = [
    ('header', rf627_old_profile_header_t),
    ('unnamed_1', union_anon_62),
    ('intensity', POINTER(rfUint8)),
    ('intensity_count', rfUint32),
]

rf627_smart_profile3D_t = struct_anon_63#	rf62X_types.h: 538

#	rf62X_types.h: 554
class struct_anon_64(Structure):
    pass

struct_anon_64.__slots__ = [
    'data',
    'data_size',
    'frame_width',
    'frame_height',
    'pixel_size',
    'user_roi_active',
    'user_roi_enabled',
    'user_roi_pos',
    'user_roi_size',
    'fact_sensor_width',
    'fact_sensor_height',
]
struct_anon_64._fields_ = [
    ('data', c_char_p),
    ('data_size', rfUint32),
    ('frame_width', rfUint32),
    ('frame_height', rfUint32),
    ('pixel_size', rfUint8),
    ('user_roi_active', rfBool),
    ('user_roi_enabled', rfBool),
    ('user_roi_pos', rfUint32),
    ('user_roi_size', rfUint32),
    ('fact_sensor_width', rfUint32),
    ('fact_sensor_height', rfUint32),
]

rf627_smart_frame_t = struct_anon_64#	rf62X_types.h: 554

#	rf62X_types.h: 570
class struct_anon_65(Structure):
    pass

struct_anon_65.__slots__ = [
    'm_Type',
    'm_CRC16',
    'm_Serial',
    'm_DataRowLength',
    'm_Width',
    'm_Height',
    'm_MultW',
    'm_MultH',
    'm_TimeStamp',
    'm_Data',
    'm_DataSize',
]
struct_anon_65._fields_ = [
    ('m_Type', rfUint16),
    ('m_CRC16', rfUint16),
    ('m_Serial', rfUint32),
    ('m_DataRowLength', rfUint32),
    ('m_Width', rfUint32),
    ('m_Height', rfUint32),
    ('m_MultW', rfUint32),
    ('m_MultH', rfUint32),
    ('m_TimeStamp', rfInt),
    ('m_Data', POINTER(rfUint8)),
    ('m_DataSize', rfUint32),
]

rf627_smart_calib_table_t = struct_anon_65#	rf62X_types.h: 570

#	rf62X_types.h: 586
class struct_anon_66(Structure):
    pass

struct_anon_66.__slots__ = [
    'device_name',
    'serial_number',
    'ip_address',
    'mac_address',
    'profile_port',
    'service_port',
    'firmware_version',
    'hardware_version',
    'z_begin',
    'z_range',
    'x_begin',
    'x_end',
]
struct_anon_66._fields_ = [
    ('device_name', c_char_p),
    ('serial_number', rfUint32),
    ('ip_address', rfUint8 * int(4)),
    ('mac_address', rfUint8 * int(6)),
    ('profile_port', rfUint16),
    ('service_port', rfUint16),
    ('firmware_version', rfUint32),
    ('hardware_version', rfUint32),
    ('z_begin', rfUint32),
    ('z_range', rfUint32),
    ('x_begin', rfUint32),
    ('x_end', rfUint32),
]

rf627_old_hello_info_by_service_protocol = struct_anon_66#	rf62X_types.h: 586

#	rf62X_types.h: 622
class struct_anon_67(Structure):
    pass

struct_anon_67.__slots__ = [
    'fact_general_firmwareVer',
    'fact_general_hardwareVer',
    'fact_general_mr',
    'fact_general_smr',
    'fact_general_xsmr',
    'fact_laser_waveLength',
    'user_general_deviceName',
    'fact_general_productCode',
    'fact_general_serial',
    'user_network_ip',
    'user_network_mask',
    'user_network_gateway',
    'user_network_hostIP',
    'fact_network_macAddr',
    'user_network_hostPort',
    'user_network_servicePort',
    'user_network_webPort',
    'user_network_speed',
    'user_network_autoNeg',
    'user_streams_udpEnabled',
    'user_streams_format',
    'fact_general_xemr',
    'fact_maxPacketSize',
]
struct_anon_67._fields_ = [
    ('fact_general_firmwareVer', c_uint32 * int(3)),
    ('fact_general_hardwareVer', c_uint32),
    ('fact_general_mr', c_uint32),
    ('fact_general_smr', c_uint32),
    ('fact_general_xsmr', c_uint32),
    ('fact_laser_waveLength', c_uint32),
    ('user_general_deviceName', String),
    ('fact_general_productCode', c_uint32),
    ('fact_general_serial', c_uint32),
    ('user_network_ip', String),
    ('user_network_mask', String),
    ('user_network_gateway', String),
    ('user_network_hostIP', String),
    ('fact_network_macAddr', String),
    ('user_network_hostPort', c_uint32),
    ('user_network_servicePort', c_uint32),
    ('user_network_webPort', c_uint32),
    ('user_network_speed', c_uint32),
    ('user_network_autoNeg', c_uint8),
    ('user_streams_udpEnabled', c_uint32),
    ('user_streams_format', c_uint32),
    ('fact_general_xemr', c_uint32),
    ('fact_maxPacketSize', c_uint32),
]

rf627_smart_hello_info_by_service_protocol = struct_anon_67#	rf62X_types.h: 622

#	rf62X_types.h: 630
class struct_anon_68(Structure):
    pass

struct_anon_68.__slots__ = [
    'value',
    'label',
    'key',
]
struct_anon_68._fields_ = [
    ('value', rfInt32),
    ('label', c_char_p),
    ('key', c_char_p),
]

enumRec_t = struct_anon_68#	rf62X_types.h: 630

#	rf62X_types.h: 636
class struct_anon_69(Structure):
    pass

struct_anon_69.__slots__ = [
    'recCount',
    'rec',
]
struct_anon_69._fields_ = [
    ('recCount', rfUint32),
    ('rec', POINTER(enumRec_t)),
]

valuesEnum_t = struct_anon_69#	rf62X_types.h: 636

#	rf62X_types.h: 647
class struct_anon_70(Structure):
    pass

struct_anon_70.__slots__ = [
    'name',
    'type',
    'access',
    'index',
    'offset',
    'size',
    'units',
]
struct_anon_70._fields_ = [
    ('name', c_char_p),
    ('type', c_char_p),
    ('access', c_char_p),
    ('index', rfUint16),
    ('offset', rfUint32),
    ('size', rfUint32),
    ('units', c_char_p),
]

value_base_t = struct_anon_70#	rf62X_types.h: 647

#	rf62X_types.h: 658
class struct_value_uint32_t(Structure):
    pass

struct_value_uint32_t.__slots__ = [
    'min',
    'max',
    'step',
    'defValue',
    'enumValues',
    'value',
]
struct_value_uint32_t._fields_ = [
    ('min', rfUint32),
    ('max', rfUint32),
    ('step', rfUint32),
    ('defValue', rfUint32),
    ('enumValues', POINTER(valuesEnum_t)),
    ('value', rfUint32),
]

value_uint32_t = struct_value_uint32_t#	rf62X_types.h: 658

#	rf62X_types.h: 668
class struct_value_uint64_t(Structure):
    pass

struct_value_uint64_t.__slots__ = [
    'min',
    'max',
    'step',
    'defValue',
    'enumValues',
    'value',
]
struct_value_uint64_t._fields_ = [
    ('min', rfUint64),
    ('max', rfUint64),
    ('step', rfUint64),
    ('defValue', rfUint64),
    ('enumValues', POINTER(valuesEnum_t)),
    ('value', rfUint64),
]

value_uint64_t = struct_value_uint64_t#	rf62X_types.h: 668

#	rf62X_types.h: 678
class struct_value_int32_t(Structure):
    pass

struct_value_int32_t.__slots__ = [
    'min',
    'max',
    'step',
    'defValue',
    'enumValues',
    'value',
]
struct_value_int32_t._fields_ = [
    ('min', rfInt32),
    ('max', rfInt32),
    ('step', rfInt32),
    ('defValue', rfInt32),
    ('enumValues', POINTER(valuesEnum_t)),
    ('value', rfInt32),
]

value_int32_t = struct_value_int32_t#	rf62X_types.h: 678

#	rf62X_types.h: 688
class struct_value_int64_t(Structure):
    pass

struct_value_int64_t.__slots__ = [
    'min',
    'max',
    'step',
    'defValue',
    'enumValues',
    'value',
]
struct_value_int64_t._fields_ = [
    ('min', rfInt64),
    ('max', rfInt64),
    ('step', rfInt64),
    ('defValue', rfInt64),
    ('enumValues', POINTER(valuesEnum_t)),
    ('value', rfInt64),
]

value_int64_t = struct_value_int64_t#	rf62X_types.h: 688

#	rf62X_types.h: 697
class struct_value_flt_t(Structure):
    pass

struct_value_flt_t.__slots__ = [
    'min',
    'max',
    'step',
    'defValue',
    'value',
]
struct_value_flt_t._fields_ = [
    ('min', rfFloat),
    ('max', rfFloat),
    ('step', rfFloat),
    ('defValue', rfFloat),
    ('value', rfFloat),
]

value_flt_t = struct_value_flt_t#	rf62X_types.h: 697

#	rf62X_types.h: 706
class struct_value_dbl_t(Structure):
    pass

struct_value_dbl_t.__slots__ = [
    'min',
    'max',
    'step',
    'defValue',
    'value',
]
struct_value_dbl_t._fields_ = [
    ('min', rfDouble),
    ('max', rfDouble),
    ('step', rfDouble),
    ('defValue', rfDouble),
    ('value', rfDouble),
]

value_dbl_t = struct_value_dbl_t#	rf62X_types.h: 706

#	rf62X_types.h: 718
class struct_array_uint32_t(Structure):
    pass

struct_array_uint32_t.__slots__ = [
    'min',
    'max',
    'step',
    'maxCount',
    'defCount',
    'defValue',
    'count',
    'value',
]
struct_array_uint32_t._fields_ = [
    ('min', rfUint32),
    ('max', rfUint32),
    ('step', rfUint32),
    ('maxCount', rfUint32),
    ('defCount', rfUint32),
    ('defValue', POINTER(rfUint32)),
    ('count', rfUint32),
    ('value', POINTER(rfUint32)),
]

array_uint32_t = struct_array_uint32_t#	rf62X_types.h: 718

#	rf62X_types.h: 730
class struct_array_uint64_t(Structure):
    pass

struct_array_uint64_t.__slots__ = [
    'min',
    'max',
    'step',
    'maxCount',
    'defCount',
    'defValue',
    'count',
    'value',
]
struct_array_uint64_t._fields_ = [
    ('min', rfUint64),
    ('max', rfUint64),
    ('step', rfUint64),
    ('maxCount', rfUint32),
    ('defCount', rfUint32),
    ('defValue', POINTER(rfUint64)),
    ('count', rfUint32),
    ('value', POINTER(rfUint64)),
]

array_uint64_t = struct_array_uint64_t#	rf62X_types.h: 730

#	rf62X_types.h: 742
class struct_array_int32_t(Structure):
    pass

struct_array_int32_t.__slots__ = [
    'min',
    'max',
    'step',
    'maxCount',
    'defCount',
    'defValue',
    'count',
    'value',
]
struct_array_int32_t._fields_ = [
    ('min', rfInt32),
    ('max', rfInt32),
    ('step', rfInt32),
    ('maxCount', rfUint32),
    ('defCount', rfUint32),
    ('defValue', POINTER(rfInt32)),
    ('count', rfUint32),
    ('value', POINTER(rfInt32)),
]

array_int32_t = struct_array_int32_t#	rf62X_types.h: 742

#	rf62X_types.h: 754
class struct_array_int64_t(Structure):
    pass

struct_array_int64_t.__slots__ = [
    'min',
    'max',
    'step',
    'maxCount',
    'defCount',
    'defValue',
    'count',
    'value',
]
struct_array_int64_t._fields_ = [
    ('min', rfInt64),
    ('max', rfInt64),
    ('step', rfInt64),
    ('maxCount', rfUint32),
    ('defCount', rfUint32),
    ('defValue', POINTER(rfInt64)),
    ('count', rfUint32),
    ('value', POINTER(rfInt64)),
]

array_int64_t = struct_array_int64_t#	rf62X_types.h: 754

#	rf62X_types.h: 766
class struct_array_flt_t(Structure):
    pass

struct_array_flt_t.__slots__ = [
    'min',
    'max',
    'step',
    'maxCount',
    'defCount',
    'defValue',
    'count',
    'value',
]
struct_array_flt_t._fields_ = [
    ('min', rfFloat),
    ('max', rfFloat),
    ('step', rfFloat),
    ('maxCount', rfUint32),
    ('defCount', rfUint32),
    ('defValue', POINTER(rfFloat)),
    ('count', rfUint32),
    ('value', POINTER(rfFloat)),
]

array_flt_t = struct_array_flt_t#	rf62X_types.h: 766

#	rf62X_types.h: 778
class struct_array_dbl_t(Structure):
    pass

struct_array_dbl_t.__slots__ = [
    'min',
    'max',
    'step',
    'maxCount',
    'defCount',
    'defValue',
    'count',
    'value',
]
struct_array_dbl_t._fields_ = [
    ('min', rfDouble),
    ('max', rfDouble),
    ('step', rfDouble),
    ('maxCount', rfUint32),
    ('defCount', rfUint32),
    ('defValue', POINTER(rfDouble)),
    ('count', rfUint32),
    ('value', POINTER(rfDouble)),
]

array_dbl_t = struct_array_dbl_t#	rf62X_types.h: 778

#	rf62X_types.h: 785
class struct_value_str_t(Structure):
    pass

struct_value_str_t.__slots__ = [
    'maxLen',
    'defValue',
    'value',
]
struct_value_str_t._fields_ = [
    ('maxLen', rfUint16),
    ('defValue', c_char_p),
    ('value', c_char_p),
]

value_str_t = struct_value_str_t#	rf62X_types.h: 785

#	rf62X_types.h: 791
class union_anon_71(Union):
    pass

union_anon_71.__slots__ = [
    'rawData',
    'val_uint32',
    'val_uint64',
    'val_int32',
    'val_int64',
    'val_flt',
    'val_dbl',
    'arr_uint32',
    'arr_uint64',
    'arr_int32',
    'arr_int64',
    'arr_flt',
    'arr_dbl',
    'val_str',
]
union_anon_71._fields_ = [
    ('rawData', POINTER(None)),
    ('val_uint32', POINTER(value_uint32_t)),
    ('val_uint64', POINTER(value_uint64_t)),
    ('val_int32', POINTER(value_int32_t)),
    ('val_int64', POINTER(value_int64_t)),
    ('val_flt', POINTER(value_flt_t)),
    ('val_dbl', POINTER(value_dbl_t)),
    ('arr_uint32', POINTER(array_uint32_t)),
    ('arr_uint64', POINTER(array_uint64_t)),
    ('arr_int32', POINTER(array_int32_t)),
    ('arr_int64', POINTER(array_int64_t)),
    ('arr_flt', POINTER(array_flt_t)),
    ('arr_dbl', POINTER(array_dbl_t)),
    ('val_str', POINTER(value_str_t)),
]

#	rf62X_types.h: 809
class struct_anon_72(Structure):
    pass

struct_anon_72.__slots__ = [
    'base',
    'unnamed_1',
    'is_changed',
]
struct_anon_72._anonymous_ = [
    'unnamed_1',
]
struct_anon_72._fields_ = [
    ('base', value_base_t),
    ('unnamed_1', union_anon_71),
    ('is_changed', c_uint8),
]

parameter_t = struct_anon_72#	rf62X_types.h: 809

#	rf62X_types.h: 817
class struct_anon_73(Structure):
    pass

struct_anon_73.__slots__ = [
    'name',
    'arg_list',
]
struct_anon_73._fields_ = [
    ('name', c_char_p),
    ('arg_list', c_void_p),
]

command_t = struct_anon_73#	rf62X_types.h: 817

#	rf62X_types.h: 822
class struct_input_t(Structure):
    pass

struct_input_t.__slots__ = [
    'size',
    'payload',
]
struct_input_t._fields_ = [
    ('size', rfUint16),
    ('payload', POINTER(rfUint8)),
]

#	rf62X_types.h: 826
class struct_output_t(Structure):
    pass

struct_output_t.__slots__ = [
    'size',
    'payload',
]
struct_output_t._fields_ = [
    ('size', rfUint16),
    ('payload', POINTER(rfUint8)),
]

#	rf62X_types.h: 830
class struct_anon_74(Structure):
    pass

struct_anon_74.__slots__ = [
    'name',
    'input',
    'output',
]
struct_anon_74._fields_ = [
    ('name', c_char_p),
    ('input', struct_input_t),
    ('output', struct_output_t),
]

command2_t = struct_anon_74#	rf62X_types.h: 830

enum_anon_75 = c_int#	rf62X_types.h: 838

kRF627_OLD = 1#	rf62X_types.h: 838

kRF627_SMART = 2#	rf62X_types.h: 838

scanner_types_t = enum_anon_75#	rf62X_types.h: 838

enum_anon_76 = c_int#	rf62X_types.h: 844

kSERVICE = 1#	rf62X_types.h: 844

kETHERNET_IP = 2#	rf62X_types.h: 844

kMODBUS_TCP = 3#	rf62X_types.h: 844

protocol_types_t = enum_anon_76#	rf62X_types.h: 844

enum_anon_77 = c_int#	rf62X_types.h: 850

kSTEP = 1#	rf62X_types.h: 850

kMEASURE = 2#	rf62X_types.h: 850

kPACKET = 3#	rf62X_types.h: 850

count_types_t = enum_anon_77#	rf62X_types.h: 850

#	rf62X_types.h: 857
class union_anon_78(Union):
    pass

union_anon_78.__slots__ = [
    'rf627old_profile2D',
    'rf627smart_profile2D',
]
union_anon_78._fields_ = [
    ('rf627old_profile2D', POINTER(rf627_old_profile2D_t)),
    ('rf627smart_profile2D', POINTER(rf627_smart_profile2D_t)),
]

#	rf62X_types.h: 861
class struct_anon_79(Structure):
    pass

struct_anon_79.__slots__ = [
    'type',
    'unnamed_1',
]
struct_anon_79._anonymous_ = [
    'unnamed_1',
]
struct_anon_79._fields_ = [
    ('type', scanner_types_t),
    ('unnamed_1', union_anon_78),
]

rf627_profile2D_t = struct_anon_79#	rf62X_types.h: 861

#	rf62X_types.h: 866
class union_anon_80(Union):
    pass

union_anon_80.__slots__ = [
    'rf627old_frame',
    'rf627smart_frame',
]
union_anon_80._fields_ = [
    ('rf627old_frame', POINTER(rf627_old_frame_t)),
    ('rf627smart_frame', POINTER(rf627_smart_frame_t)),
]

#	rf62X_types.h: 870
class struct_anon_81(Structure):
    pass

struct_anon_81.__slots__ = [
    'type',
    'unnamed_1',
]
struct_anon_81._anonymous_ = [
    'unnamed_1',
]
struct_anon_81._fields_ = [
    ('type', scanner_types_t),
    ('unnamed_1', union_anon_80),
]

rf627_frame_t = struct_anon_81#	rf62X_types.h: 870

#	rf62X_types.h: 875
class union_anon_82(Union):
    pass

union_anon_82.__slots__ = [
    'rf627old_calib_table',
    'rf627smart_calib_table',
]
union_anon_82._fields_ = [
    ('rf627old_calib_table', POINTER(rf627_old_calib_table_t)),
    ('rf627smart_calib_table', POINTER(rf627_smart_calib_table_t)),
]

#	rf62X_types.h: 879
class struct_anon_83(Structure):
    pass

struct_anon_83.__slots__ = [
    'type',
    'unnamed_1',
]
struct_anon_83._anonymous_ = [
    'unnamed_1',
]
struct_anon_83._fields_ = [
    ('type', scanner_types_t),
    ('unnamed_1', union_anon_82),
]

rf627_calib_table_t = struct_anon_83#	rf62X_types.h: 879

#	rf62X_types.h: 886
class union_anon_84(Union):
    pass

union_anon_84.__slots__ = [
    'rf627_profile3D',
    'rf627smart_profile3D',
]
union_anon_84._fields_ = [
    ('rf627_profile3D', POINTER(rf627_old_profile3D_t)),
    ('rf627smart_profile3D', POINTER(rf627_smart_profile3D_t)),
]

#	rf62X_types.h: 890
class struct_anon_85(Structure):
    pass

struct_anon_85.__slots__ = [
    'type',
    'unnamed_1',
]
struct_anon_85._anonymous_ = [
    'unnamed_1',
]
struct_anon_85._fields_ = [
    ('type', scanner_types_t),
    ('unnamed_1', union_anon_84),
]

rf627_profile3D_t = struct_anon_85#	rf62X_types.h: 890

#	rf62X_types.h: 899
class union_anon_86(Union):
    pass

union_anon_86.__slots__ = [
    'hello_info_service_protocol',
]
union_anon_86._fields_ = [
    ('hello_info_service_protocol', POINTER(rf627_old_hello_info_by_service_protocol)),
]

#	rf62X_types.h: 902
class union_anon_87(Union):
    pass

union_anon_87.__slots__ = [
    'hello_info_service_protocol',
]
union_anon_87._fields_ = [
    ('hello_info_service_protocol', POINTER(rf627_smart_hello_info_by_service_protocol)),
]

#	rf62X_types.h: 898
class union_anon_88(Union):
    pass

union_anon_88.__slots__ = [
    'rf627old',
    'rf627smart',
]
union_anon_88._fields_ = [
    ('rf627old', union_anon_86),
    ('rf627smart', union_anon_87),
]

#	rf62X_types.h: 906
class struct_anon_89(Structure):
    pass

struct_anon_89.__slots__ = [
    'scanner_type',
    'protocol_type',
    'unnamed_1',
]
struct_anon_89._anonymous_ = [
    'unnamed_1',
]
struct_anon_89._fields_ = [
    ('scanner_type', scanner_types_t),
    ('protocol_type', protocol_types_t),
    ('unnamed_1', union_anon_88),
]

hello_information = struct_anon_89#	rf62X_types.h: 906

#	custom_vector.h: 10
class struct_vector_(Structure):
    pass

struct_vector_.__slots__ = [
    'data',
    'size',
    'count',
]
struct_vector_._fields_ = [
    ('data', POINTER(POINTER(None))),
    ('size', rfSize),
    ('count', rfSize),
]

vector_t = struct_vector_#	custom_vector.h: 10

WINBOOL = c_int# c:\\mingw\\include\\windef.h: 246

BOOL = WINBOOL# c:\\mingw\\include\\windef.h: 250

u_char = c_ubyte# c:\\mingw\\include\\sys\\bsdtypes.h: 59

u_short = c_ushort# c:\\mingw\\include\\sys\\bsdtypes.h: 60

u_int = c_uint# c:\\mingw\\include\\sys\\bsdtypes.h: 61

u_long = c_ulong# c:\\mingw\\include\\sys\\bsdtypes.h: 62

SOCKET = u_int# c:\\mingw\\include\\winsock.h: 103

# c:\\mingw\\include\\winsock.h: 322
class struct_anon_340(Structure):
    pass

struct_anon_340.__slots__ = [
    's_b1',
    's_b2',
    's_b3',
    's_b4',
]
struct_anon_340._fields_ = [
    ('s_b1', u_char),
    ('s_b2', u_char),
    ('s_b3', u_char),
    ('s_b4', u_char),
]

# c:\\mingw\\include\\winsock.h: 323
class struct_anon_341(Structure):
    pass

struct_anon_341.__slots__ = [
    's_w1',
    's_w2',
]
struct_anon_341._fields_ = [
    ('s_w1', u_short),
    ('s_w2', u_short),
]

# c:\\mingw\\include\\winsock.h: 321
class union_anon_342(Union):
    pass

union_anon_342.__slots__ = [
    'S_un_b',
    'S_un_w',
    'S_addr',
]
union_anon_342._fields_ = [
    ('S_un_b', struct_anon_340),
    ('S_un_w', struct_anon_341),
    ('S_addr', u_long),
]

# c:\\mingw\\include\\winsock.h: 314
class struct_in_addr(Structure):
    pass

struct_in_addr.__slots__ = [
    'S_un',
]
struct_in_addr._fields_ = [
    ('S_un', union_anon_342),
]

# c:\\mingw\\include\\winsock.h: 347
class struct_sockaddr_in(Structure):
    pass

struct_sockaddr_in.__slots__ = [
    'sin_family',
    'sin_port',
    'sin_addr',
    'sin_zero',
]
struct_sockaddr_in._fields_ = [
    ('sin_family', c_short),
    ('sin_port', u_short),
    ('sin_addr', struct_in_addr),
    ('sin_zero', c_char * int(8)),
]

#	udpport.h: 35
class struct_anon_360(Structure):
    pass

struct_anon_360.__slots__ = [
    'port_num',
    'input_addr',
    'output_addr',
    'init_flag',
    'sock',
]
struct_anon_360._fields_ = [
    ('port_num', c_uint16),
    ('input_addr', struct_sockaddr_in),
    ('output_addr', struct_sockaddr_in),
    ('init_flag', c_uint8),
    ('sock', SOCKET),
]

udp_port_t = struct_anon_360#	udpport.h: 35

# c:\\mingw\\include\\pthread.h: 400
class struct_anon_368(Structure):
    pass

struct_anon_368.__slots__ = [
    'p',
    'x',
]
struct_anon_368._fields_ = [
    ('p', POINTER(None)),
    ('x', c_uint),
]

ptw32_handle_t = struct_anon_368# c:\\mingw\\include\\pthread.h: 400

pthread_t = ptw32_handle_t# c:\\mingw\\include\\pthread.h: 402

# c:\\mingw\\include\\pthread.h: 406
class struct_pthread_mutex_t_(Structure):
    pass

pthread_mutex_t = POINTER(struct_pthread_mutex_t_)# c:\\mingw\\include\\pthread.h: 406

# c:\\mingw\\include\\pthread.h: 408
class struct_pthread_cond_t_(Structure):
    pass

pthread_cond_t = POINTER(struct_pthread_cond_t_)# c:\\mingw\\include\\pthread.h: 408

RF62X_answ_callback = CFUNCTYPE(UNCHECKED(c_int8), String, c_uint32, c_uint32, POINTER(None))#	RF62Xtypes.h: 10

RF62X_timeout_callback = CFUNCTYPE(UNCHECKED(c_int8), POINTER(None))#	RF62Xtypes.h: 13

RF62X_free_callback = CFUNCTYPE(UNCHECKED(c_int8), POINTER(None))#	RF62Xtypes.h: 15

#	RF62Xtypes.h: 46
class struct_anon_371(Structure):
    pass

struct_anon_371.__slots__ = [
    'type',
    'cmd_name',
    'container_type',
    'check_crc_flag',
    'confirmation_flag',
    'one_answ_flag',
    'wait_answ_flag',
    'data',
    'data_size',
    '_answ_clb',
    '_timeout_clb',
    '_free_clb',
    '_msg_uid',
    '_device_id',
    '_uid',
    '_sending_time',
    '_timeout',
    '_resends',
    'state',
    'result',
    'result_mutex',
]
struct_anon_371._fields_ = [
    ('type', c_char * int(64)),
    ('cmd_name', c_char * int(256)),
    ('container_type', c_char * int(64)),
    ('check_crc_flag', c_uint8),
    ('confirmation_flag', c_uint8),
    ('one_answ_flag', c_uint8),
    ('wait_answ_flag', c_uint8),
    ('data', String),
    ('data_size', c_uint32),
    ('_answ_clb', RF62X_answ_callback),
    ('_timeout_clb', RF62X_timeout_callback),
    ('_free_clb', RF62X_free_callback),
    ('_msg_uid', c_uint64),
    ('_device_id', c_uint64),
    ('_uid', c_uint64),
    ('_sending_time', c_uint32),
    ('_timeout', c_uint32),
    ('_resends', c_uint32),
    ('state', c_uint16),
    ('result', POINTER(None)),
    ('result_mutex', POINTER(pthread_mutex_t)),
]

RF62X_msg_t = struct_anon_371#	RF62Xtypes.h: 46

#	RF62Xtypes.h: 72
class struct_anon_373(Structure):
    pass

struct_anon_373.__slots__ = [
    'msg',
    'data_pos',
]
struct_anon_373._fields_ = [
    ('msg', POINTER(RF62X_msg_t)),
    ('data_pos', c_uint32),
]

RF62X_parser_output_msg_t = struct_anon_373#	RF62Xtypes.h: 72

#	RF62Xtypes.h: 82
class struct_anon_374(Structure):
    pass

struct_anon_374.__slots__ = [
    'msg',
    'mask',
    'received_size',
    'data_pos',
]
struct_anon_374._fields_ = [
    ('msg', POINTER(RF62X_msg_t)),
    ('mask', POINTER(c_uint8)),
    ('received_size', c_uint32),
    ('data_pos', c_uint32),
]

RF62X_parser_input_msg_t = struct_anon_374#	RF62Xtypes.h: 82

#	RF62Xtypes.h: 93
class struct_anon_375(Structure):
    pass

struct_anon_375.__slots__ = [
    'data',
    'data_pos',
    'data_size',
    'data_id',
    'is_data_confirmed',
]
struct_anon_375._fields_ = [
    ('data', POINTER(c_uint8)),
    ('data_pos', c_uint32),
    ('data_size', c_uint32),
    ('data_id', c_uint32),
    ('is_data_confirmed', c_uint8),
]

RF62X_parser_output_data_t = struct_anon_375#	RF62Xtypes.h: 93

#	RF62Xtypes.h: 105
class struct_anon_376(Structure):
    pass

struct_anon_376.__slots__ = [
    'data',
    'mask',
    'chain_size',
    'data_size',
    'data_pos',
    'msg_uid',
    'uid',
    'cmd_name',
]
struct_anon_376._fields_ = [
    ('data', POINTER(c_uint8)),
    ('mask', POINTER(c_uint8)),
    ('chain_size', c_uint32),
    ('data_size', c_uint32),
    ('data_pos', c_uint32),
    ('msg_uid', c_uint32),
    ('uid', c_uint32),
    ('cmd_name', String),
]

RF62X_parser_input_data = struct_anon_376#	RF62Xtypes.h: 105

#	RF62Xtypes.h: 185
class struct_anon_377(Structure):
    pass

struct_anon_377.__slots__ = [
    'output_msg_buffer',
    'output_msg_index',
    'input_msg_buffer',
    'input_msg_index',
    'output_data',
    'output_msg_buff_mutex',
    'output_data_index',
    'output_data_id',
    'output_data_cmd_name',
    'input_data',
    'input_data_index',
    'input_data_cmd_name',
    'input_msg_buff_mutex',
    'input_data_cond_var_mutex',
    'input_data_cond_var',
    'input_wait_confirm_var_mutex',
    'input_wait_confirm_cond_var',
    'input_data_cond_var_flag',
    'input_wait_confirm_cond_var_flag',
    'instance_mutex',
    'max_data_size',
    'max_packet_size',
    'host_device_uid',
    'detected_lost_data',
    'detected_lost_data_size',
    'detected_lost_data_pos',
    'lost_full_data_size',
    'detected_lost_data_id',
    'detected_lost_data_logic_port',
    'packet_data_buff',
    'packet_data_pos',
    'packet_data_mutex',
    'serial_packet_size',
    'data_packet_flag',
    'lost_data_request_packet',
    'data_confirmation_packet',
]
struct_anon_377._fields_ = [
    ('output_msg_buffer', POINTER(RF62X_parser_output_msg_t)),
    ('output_msg_index', c_uint32),
    ('input_msg_buffer', POINTER(RF62X_parser_input_msg_t)),
    ('input_msg_index', c_uint32),
    ('output_data', POINTER(RF62X_parser_output_data_t)),
    ('output_msg_buff_mutex', pthread_mutex_t),
    ('output_data_index', c_uint32),
    ('output_data_id', c_uint8),
    ('output_data_cmd_name', c_char * int(256)),
    ('input_data', POINTER(RF62X_parser_input_data)),
    ('input_data_index', c_uint32),
    ('input_data_cmd_name', c_char * int(256)),
    ('input_msg_buff_mutex', pthread_mutex_t),
    ('input_data_cond_var_mutex', pthread_mutex_t),
    ('input_data_cond_var', pthread_cond_t),
    ('input_wait_confirm_var_mutex', pthread_mutex_t),
    ('input_wait_confirm_cond_var', pthread_cond_t),
    ('input_data_cond_var_flag', c_uint8),
    ('input_wait_confirm_cond_var_flag', c_uint8),
    ('instance_mutex', pthread_mutex_t),
    ('max_data_size', c_uint32),
    ('max_packet_size', c_uint16),
    ('host_device_uid', c_uint32),
    ('detected_lost_data', POINTER(c_uint8)),
    ('detected_lost_data_size', c_uint32),
    ('detected_lost_data_pos', c_uint32),
    ('lost_full_data_size', c_uint32),
    ('detected_lost_data_id', c_uint8),
    ('detected_lost_data_logic_port', c_uint8),
    ('packet_data_buff', POINTER(c_uint8)),
    ('packet_data_pos', c_uint32),
    ('packet_data_mutex', pthread_mutex_t),
    ('serial_packet_size', c_uint16),
    ('data_packet_flag', c_uint8),
    ('lost_data_request_packet', POINTER(c_uint8)),
    ('data_confirmation_packet', POINTER(c_uint8)),
]

RF62X_parser_t = struct_anon_377#	RF62Xtypes.h: 185

#	RF62Xtypes.h: 213
class struct_anon_378(Structure):
    pass

struct_anon_378.__slots__ = [
    'RF62X_parser',
    'dst_ip_addr',
    'host_ip_addr',
    'RF62X_sock',
    'host_udp_port',
    'dst_udp_port',
    'socket_timeout',
    'instance_mutex',
    'output_udpport_mutex',
    'global_mutex',
    'instance_index',
    'read_thread',
    'thread_stop_flag',
    'output_packet_data',
    'max_packet_size',
    'max_data_size',
]
struct_anon_378._fields_ = [
    ('RF62X_parser', RF62X_parser_t),
    ('dst_ip_addr', c_uint32),
    ('host_ip_addr', c_uint32),
    ('RF62X_sock', udp_port_t),
    ('host_udp_port', c_uint16),
    ('dst_udp_port', c_uint16),
    ('socket_timeout', c_uint32),
    ('instance_mutex', pthread_mutex_t),
    ('output_udpport_mutex', pthread_mutex_t),
    ('global_mutex', pthread_mutex_t),
    ('instance_index', c_int32),
    ('read_thread', pthread_t),
    ('thread_stop_flag', c_uint8),
    ('output_packet_data', POINTER(c_uint8)),
    ('max_packet_size', c_uint16),
    ('max_data_size', c_uint32),
]

RF62X_channel_t = struct_anon_378#	RF62Xtypes.h: 213

#	rf62X_devices.h: 32
class struct_anon_420(Structure):
    pass

struct_anon_420.__slots__ = [
    'options',
    'factory_params',
    'user_params',
    'm_svc_sock',
    'm_data_sock',
    'msg_count',
    'host_ip',
    'params_list',
    'info_by_service_protocol',
]
struct_anon_420._fields_ = [
    ('options', config_options_t),
    ('factory_params', rf627_old_factory_params_t),
    ('user_params', rf627_old_user_params_t),
    ('m_svc_sock', POINTER(None)),
    ('m_data_sock', POINTER(None)),
    ('msg_count', rfUint16),
    ('host_ip', rfUint32),
    ('params_list', POINTER(vector_t)),
    ('info_by_service_protocol', rf627_old_hello_info_by_service_protocol),
]

rf627_old_t = struct_anon_420#	rf62X_devices.h: 32

#	rf62X_devices.h: 218
class struct_anon_421(Structure):
    pass

struct_anon_421.__slots__ = [
    'channel',
    'm_data_sock',
    'params_list',
    'info_by_service_protocol',
    'calib_table',
    'is_connected',
]
struct_anon_421._fields_ = [
    ('channel', RF62X_channel_t),
    ('m_data_sock', POINTER(None)),
    ('params_list', POINTER(vector_t)),
    ('info_by_service_protocol', rf627_smart_hello_info_by_service_protocol),
    ('calib_table', rf627_smart_calib_table_t),
    ('is_connected', rfBool),
]

rf627_smart_t = struct_anon_421#	rf62X_devices.h: 218

#	rf62X_devices.h: 591
class union_anon_422(Union):
    pass

union_anon_422.__slots__ = [
    'rf627_old',
    'rf627_smart',
]
union_anon_422._fields_ = [
    ('rf627_old', POINTER(rf627_old_t)),
    ('rf627_smart', POINTER(rf627_smart_t)),
]

#	rf62X_devices.h: 595
class struct_anon_423(Structure):
    pass

struct_anon_423.__slots__ = [
    'type',
    'unnamed_1',
]
struct_anon_423._anonymous_ = [
    'unnamed_1',
]
struct_anon_423._fields_ = [
    ('type', scanner_types_t),
    ('unnamed_1', union_anon_422),
]

scanner_base_t = struct_anon_423#	rf62X_devices.h: 595

#	rf62X_sdk.h: 18
try:
    STREAM_SOCK_RECV_TIMEOUT = 100
except:
    pass

value_uint32_t = struct_value_uint32_t#	rf62X_types.h: 658

value_uint64_t = struct_value_uint64_t#	rf62X_types.h: 668

value_int32_t = struct_value_int32_t#	rf62X_types.h: 678

value_int64_t = struct_value_int64_t#	rf62X_types.h: 688

value_flt_t = struct_value_flt_t#	rf62X_types.h: 697

value_dbl_t = struct_value_dbl_t#	rf62X_types.h: 706

array_uint32_t = struct_array_uint32_t#	rf62X_types.h: 718

array_uint64_t = struct_array_uint64_t#	rf62X_types.h: 730

array_int32_t = struct_array_int32_t#	rf62X_types.h: 742

array_int64_t = struct_array_int64_t#	rf62X_types.h: 754

array_flt_t = struct_array_flt_t#	rf62X_types.h: 766

array_dbl_t = struct_array_dbl_t#	rf62X_types.h: 778

value_str_t = struct_value_str_t#	rf62X_types.h: 785

input_t = struct_input_t#	rf62X_types.h: 822

output_t = struct_output_t#	rf62X_types.h: 826

vector_ = struct_vector_#	custom_vector.h: 10

#	custom_vector.h: 15
lib.vector_init.argtypes = [POINTER(vector_t)]
lib.vector_init.restype = None
#	custom_vector.h: 20
lib.vector_count.argtypes = [POINTER(vector_t)]
lib.vector_count.restype = rfSize
#	custom_vector.h: 28
lib.vector_add.argtypes = [POINTER(vector_t), POINTER(None)]
lib.vector_add.restype = None
#	custom_vector.h: 37
lib.vector_set.argtypes = [POINTER(vector_t), rfSize, POINTER(None)]
lib.vector_set.restype = None
#	custom_vector.h: 45
lib.vector_get.argtypes = [POINTER(vector_t), rfSize]
lib.vector_get.restype = POINTER(c_ubyte)
lib.vector_get.errcheck = lambda v,*a : cast(v, c_void_p)
#	custom_vector.h: 52
lib.vector_empty.argtypes = [POINTER(vector_t)]
lib.vector_empty.restype = rfSize
#	custom_vector.h: 60
lib.vector_delete.argtypes = [POINTER(vector_t), rfSize]
lib.vector_delete.restype = None
#	custom_vector.h: 67
lib.vector_free.argtypes = [POINTER(vector_t)]
lib.vector_free.restype = None
#	custom_vector.h: 74
lib.vector_begin.argtypes = [POINTER(vector_t)]
lib.vector_begin.restype = POINTER(c_ubyte)
lib.vector_begin.errcheck = lambda v,*a : cast(v, c_void_p)
#	custom_vector.h: 81
lib.vector_end.argtypes = [POINTER(vector_t)]
lib.vector_end.restype = POINTER(c_ubyte)
lib.vector_end.errcheck = lambda v,*a : cast(v, c_void_p)
#	rf62X_sdk.h: 35
lib.set_platform_adapter_settings.argtypes = [rfUint32, rfUint32]
lib.set_platform_adapter_settings.restype = None
#	rf62X_sdk.h: 50
lib.search_scanners.argtypes = [POINTER(vector_t), scanner_types_t, rfUint32, protocol_types_t]
lib.search_scanners.restype = rfUint8
#	rf62X_sdk.h: 54
lib.search_scanners_by_ip.argtypes = [POINTER(vector_t), scanner_types_t, c_char_p, rfUint32, protocol_types_t]
lib.search_scanners_by_ip.restype = rfUint8
#	rf62X_sdk.h: 67
lib.get_info_about_scanner.argtypes = [POINTER(scanner_base_t), protocol_types_t]
lib.get_info_about_scanner.restype = hello_information
#	rf62X_sdk.h: 78
lib.connect_to_scanner.argtypes = [POINTER(scanner_base_t), protocol_types_t]
lib.connect_to_scanner.restype = rfUint8
#	rf62X_sdk.h: 90
lib.check_connection_to_scanner.argtypes = [POINTER(scanner_base_t), rfUint32, protocol_types_t]
lib.check_connection_to_scanner.restype = rfUint8
#	rf62X_sdk.h: 102
lib.disconnect_from_scanner.argtypes = [POINTER(scanner_base_t), protocol_types_t]
lib.disconnect_from_scanner.restype = rfUint8
#	rf62X_sdk.h: 111
lib.free_scanner.argtypes = [POINTER(scanner_base_t)]
lib.free_scanner.restype = None
#	rf62X_sdk.h: 124
lib.get_profile2D_from_scanner.argtypes = [POINTER(scanner_base_t), rfBool, rfBool, protocol_types_t]
lib.get_profile2D_from_scanner.restype = POINTER(rf627_profile2D_t)
#	rf62X_sdk.h: 136
lib.send_profile2D_request_to_scanner.argtypes = [POINTER(scanner_base_t), rfUint32, protocol_types_t]
lib.send_profile2D_request_to_scanner.restype = c_uint8
#	rf62X_sdk.h: 144
lib.free_profile2D.argtypes = [POINTER(rf627_profile2D_t)]
lib.free_profile2D.restype = None
#	rf62X_sdk.h: 157
lib.get_profile3D_from_scanner.argtypes = [POINTER(scanner_base_t), rfFloat, rfFloat, count_types_t, rfBool, protocol_types_t]
lib.get_profile3D_from_scanner.restype = POINTER(rf627_profile3D_t)
#	rf62X_sdk.h: 169
lib.get_frame_from_scanner.argtypes = [POINTER(scanner_base_t), protocol_types_t]
lib.get_frame_from_scanner.restype = POINTER(rf627_frame_t)
#	rf62X_sdk.h: 182
lib.read_params_from_scanner.argtypes = [POINTER(scanner_base_t), rfUint32, protocol_types_t]
lib.read_params_from_scanner.restype = rfUint8
#	rf62X_sdk.h: 194
lib.write_params_to_scanner.argtypes = [POINTER(scanner_base_t), rfUint32, protocol_types_t]
lib.write_params_to_scanner.restype = rfUint8
#	rf62X_sdk.h: 205
lib.save_params_to_scanner.argtypes = [POINTER(scanner_base_t), rfUint32, protocol_types_t]
lib.save_params_to_scanner.restype = rfUint8
#	rf62X_sdk.h: 214
lib.load_recovery_params_from_scanner.argtypes = [POINTER(scanner_base_t), c_uint32, protocol_types_t]
lib.load_recovery_params_from_scanner.restype = rfUint8
#	rf62X_sdk.h: 225
lib.get_parameter.argtypes = [POINTER(scanner_base_t), c_char_p]
lib.get_parameter.restype = POINTER(parameter_t)
#	rf62X_sdk.h: 236
lib.set_parameter.argtypes = [POINTER(scanner_base_t), POINTER(parameter_t)]
lib.set_parameter.restype = rfUint8
#	rf62X_sdk.h: 239
lib.create_parameter_from_type.argtypes = [c_char_p]
lib.create_parameter_from_type.restype = POINTER(parameter_t)
#	rf62X_sdk.h: 247
lib.free_parameter.argtypes = [POINTER(parameter_t), scanner_types_t]
lib.free_parameter.restype = None
#	rf62X_sdk.h: 258
lib.set_parameter_by_name.argtypes = [POINTER(scanner_base_t), String, rfUint32, c_void_p]
lib.set_parameter_by_name.restype = rfUint8
#	rf62X_sdk.h: 275
lib.get_dumps_profiles_from_scanner.argtypes = [POINTER(scanner_base_t), c_uint32, c_uint32, c_uint32, protocol_types_t, POINTER(POINTER(rf627_profile2D_t)), POINTER(c_uint32), c_uint32]
lib.get_dumps_profiles_from_scanner.restype = rfUint8
#	rf62X_sdk.h: 290
lib.get_authorization_token_from_scanner.argtypes = [POINTER(scanner_base_t), POINTER(POINTER(c_char)), POINTER(c_uint32), c_uint32, protocol_types_t]
lib.get_authorization_token_from_scanner.restype = rfUint8
#	rf62X_sdk.h: 303
lib.set_authorization_key_to_scanner.argtypes = [POINTER(scanner_base_t), String, c_uint32, c_uint32, protocol_types_t]
lib.set_authorization_key_to_scanner.restype = rfUint8
#	rf62X_sdk.h: 315
lib.read_calibration_table_from_scanner.argtypes = [POINTER(scanner_base_t), c_uint32, protocol_types_t]
lib.read_calibration_table_from_scanner.restype = rfUint8
#	rf62X_sdk.h: 325
lib.convert_calibration_table_from_bytes.argtypes = [String, c_uint32]
lib.convert_calibration_table_from_bytes.restype = POINTER(rf627_calib_table_t)
#	rf62X_sdk.h: 336
lib.convert_calibration_table_to_bytes.argtypes = [POINTER(rf627_calib_table_t), POINTER(POINTER(c_char)), POINTER(c_uint32)]
lib.convert_calibration_table_to_bytes.restype = rfBool
#	rf62X_sdk.h: 347
lib.write_calibration_table_to_scanner.argtypes = [POINTER(scanner_base_t), c_uint32, protocol_types_t]
lib.write_calibration_table_to_scanner.restype = rfUint8
#	rf62X_sdk.h: 358
lib.get_calibration_table_from_scanner.argtypes = [POINTER(scanner_base_t), c_uint32, protocol_types_t]
lib.get_calibration_table_from_scanner.restype = POINTER(rf627_calib_table_t)
#	rf62X_sdk.h: 370
lib.set_calibration_table_to_scanner.argtypes = [POINTER(scanner_base_t), POINTER(rf627_calib_table_t), c_uint32, protocol_types_t]
lib.set_calibration_table_to_scanner.restype = rfUint8
#	rf62X_sdk.h: 382
lib.save_calibration_table_to_scanner.argtypes = [POINTER(scanner_base_t), c_uint32, protocol_types_t]
lib.save_calibration_table_to_scanner.restype = rfUint8
#	rf62X_sdk.h: 391
lib.send_reboot_device_request_to_scanner.argtypes = [POINTER(scanner_base_t), protocol_types_t]
lib.send_reboot_device_request_to_scanner.restype = c_uint8
#	rf62X_sdk.h: 400
lib.send_reboot_sensor_request_to_scanner.argtypes = [POINTER(scanner_base_t), protocol_types_t]
lib.send_reboot_sensor_request_to_scanner.restype = c_uint8
#	rf62X_sdk.h: 409
lib.send_data_to_scanner_periphery.argtypes = [POINTER(scanner_base_t), c_char_p, rfUint32, c_char_p, rfUint32, POINTER(c_char_p), POINTER(rfUint32)]
lib.send_data_to_scanner_periphery.restype = c_uint8
#	rf62X_sdk.h: 419
lib.receive_data_from_scanner_periphery.argtypes = [POINTER(scanner_base_t), c_char_p, rfUint32, rfUint16, POINTER(c_char_p), POINTER(rfUint32)]
lib.receive_data_from_scanner_periphery.restype = c_uint8
#	rf62X_sdk.h: 430
lib.send_command.argtypes = [POINTER(scanner_base_t), POINTER(command_t)]
lib.send_command.restype = rfUint8
#	rf62X_sdk.h: 439
lib.send_command2.argtypes = [POINTER(scanner_base_t), POINTER(command2_t)]
lib.send_command2.restype = rfUint8
#	rf62Xcore.h: 21
lib.core_init.argtypes = []
lib.core_init.restype = c_int8
#	rf62Xcore.h: 28
lib.sdk_version.argtypes = []
if sizeof(c_int) == sizeof(c_void_p):
    lib.sdk_version.restype = ReturnString
else:
    lib.sdk_version.restype = String
    lib.sdk_version.errcheck = ReturnString
#	rf62Xcore.h: 34
lib.core_cleanup.argtypes = []
lib.core_cleanup.restype = None
#	rf62Xcore.h: 44
lib.platform_calloc.argtypes = [rfSize, rfSize]
lib.platform_calloc.restype = POINTER(c_ubyte)
lib.platform_calloc.errcheck = lambda v,*a : cast(v, c_void_p)
#	rf62Xcore.h: 55
lib.platform_malloc.argtypes = [rfSize]
lib.platform_malloc.restype = POINTER(c_ubyte)
lib.platform_malloc.errcheck = lambda v,*a : cast(v, c_void_p)
#	rf62Xcore.h: 66
lib.platform_realloc.argtypes = [POINTER(None), rfSize]
lib.platform_realloc.restype = POINTER(c_ubyte)
lib.platform_realloc.errcheck = lambda v,*a : cast(v, c_void_p)
#	rf62Xcore.h: 72
lib.platform_free.argtypes = [POINTER(None)]
lib.platform_free.restype = None
#	rf62Xcore.h: 84
lib.platform_memset.argtypes = [POINTER(None), rfInt, rfSize]
lib.platform_memset.restype = POINTER(c_ubyte)
lib.platform_memset.errcheck = lambda v,*a : cast(v, c_void_p)
#	rf62Xcore.h: 97
lib.platform_memcpy.argtypes = [POINTER(None), POINTER(None), rfSize]
lib.platform_memcpy.restype = POINTER(c_ubyte)
lib.platform_memcpy.errcheck = lambda v,*a : cast(v, c_void_p)
#	rf62Xcore.h: 113
lib.platform_memcmp.argtypes = [POINTER(None), POINTER(None), c_size_t]
lib.platform_memcmp.restype = rfInt
#	rf62Xcore.h: 126
lib.platform_htonl.argtypes = [rfUint32]
lib.platform_htonl.restype = rfUint32
#	rf62Xcore.h: 134
lib.platform_ntohl.argtypes = [rfUint32]
lib.platform_ntohl.restype = rfUint32
#	rf62Xcore.h: 141
lib.platform_htons.argtypes = [rfUint16]
lib.platform_htons.restype = rfUint16
#	rf62Xcore.h: 148
lib.platform_ntohs.argtypes = [rfUint16]
lib.platform_ntohs.restype = rfUint16
#	rf62Xcore.h: 159
lib.platform_create_udp_socket.argtypes = []
lib.platform_create_udp_socket.restype = POINTER(c_ubyte)
lib.platform_create_udp_socket.errcheck = lambda v,*a : cast(v, c_void_p)
#	rf62Xcore.h: 172
lib.platform_set_broadcast_socket_option.argtypes = [POINTER(None)]
lib.platform_set_broadcast_socket_option.restype = rfInt8
#	rf62Xcore.h: 185
lib.platform_set_reuseaddr_socket_option.argtypes = [POINTER(None)]
lib.platform_set_reuseaddr_socket_option.restype = rfInt8
#	rf62Xcore.h: 198
lib.platform_set_socket_option.argtypes = [POINTER(None), rfInt32, rfInt32, c_char_p, rfInt32]
lib.platform_set_socket_option.restype = rfInt8
#	rf62Xcore.h: 210
lib.platform_set_socket_recv_timeout.argtypes = [POINTER(None), rfInt32]
lib.platform_set_socket_recv_timeout.restype = rfInt8
#	rf62Xcore.h: 221
lib.platform_socket_connect.argtypes = [POINTER(None), rfUint32, rfUint16]
lib.platform_socket_connect.restype = rfInt8
#	rf62Xcore.h: 233
lib.platform_socket_bind.argtypes = [POINTER(None), rfUint32, rfUint16]
lib.platform_socket_bind.restype = rfInt
#	rf62Xcore.h: 244
lib.platform_socket_listen.argtypes = [POINTER(None), rfInt32]
lib.platform_socket_listen.restype = rfInt8
#	rf62Xcore.h: 263
lib.platform_socket_accept.argtypes = [POINTER(None), POINTER(rfUint32), POINTER(rfUint16)]
lib.platform_socket_accept.restype = POINTER(c_ubyte)
lib.platform_socket_accept.errcheck = lambda v,*a : cast(v, c_void_p)
#	rf62Xcore.h: 273
lib.platform_close_socket.argtypes = [POINTER(None)]
lib.platform_close_socket.restype = rfInt8
#	rf62Xcore.h: 285
lib.platform_send_tcp_data.argtypes = [POINTER(None), POINTER(None), rfSize]
lib.platform_send_tcp_data.restype = rfInt
#	rf62Xcore.h: 299
lib.platform_send_udp_data.argtypes = [POINTER(None), POINTER(None), rfSize, rfUint32, rfUint16]
lib.platform_send_udp_data.restype = rfInt
#	rf62Xcore.h: 312
lib.platform_recv_from.argtypes = [POINTER(None), POINTER(None), rfSize, POINTER(rfUint32), POINTER(rfUint16)]
lib.platform_recv_from.restype = rfInt
#	rf62Xcore.h: 323
lib.platform_recv.argtypes = [POINTER(None), POINTER(None), rfSize]
lib.platform_recv.restype = rfInt
#	network.h: 39
lib.GetAdaptersCount.argtypes = []
lib.GetAdaptersCount.restype = c_int
#	network.h: 41
lib.GetAdapterAddress.argtypes = [c_int]
lib.GetAdapterAddress.restype = c_char_p
#	network.h: 42
lib.GetAdapterMasks.argtypes = [c_int]
lib.GetAdapterMasks.restype = c_char_p
if platform.system()=='Windows':
    #	network.h: 45
    lib.WinSockInit.argtypes = []
    lib.WinSockInit.restype = BOOL
    #	network.h: 47
    lib.WinSockDeinit.argtypes = []
    lib.WinSockDeinit.restype = None
#	network.h: 49
lib.EnumAdapterAddresses.argtypes = []
lib.EnumAdapterAddresses.restype = BOOL
#	network.h: 54
lib.FreeAdapterAddresses.argtypes = []
lib.FreeAdapterAddresses.restype = None
#	network.h: 56
lib.MatchIP.argtypes = [String, String, String]
lib.MatchIP.restype = BOOL
#	network.h: 68
lib.GetCompatibleInterface.argtypes = [String, String]
if sizeof(c_int) == sizeof(c_void_p):
    lib.GetCompatibleInterface.restype = ReturnString
else:
    lib.GetCompatibleInterface.restype = String
    lib.GetCompatibleInterface.errcheck = ReturnString
#	network.h: 83
lib.MatchUDP.argtypes = [u_long, u_long]
lib.MatchUDP.restype = BOOL
#	network.h: 85
lib.GetUDPCompatibleInterface.argtypes = [u_long]
lib.GetUDPCompatibleInterface.restype = u_long
#	network.h: 87
lib.DumpInterfaces.argtypes = []
class PARAM_VALUE_TYPE(IntEnum):

    UNKN_PARAM_TYPE         = 0,
    UINT_PARAM_TYPE         = 1,
    UINT64_PARAM_TYPE       = 2,
    INT_PARAM_TYPE          = 3,
    INT64_PARAM_TYPE        = 4,
    FLOAT_PARAM_TYPE        = 5,
    DOUBLE_PARAM_TYPE       = 6,
    UINT32_ARRAY_PARAM_TYPE = 7,
    UINT64_ARRAY_PARAM_TYPE = 8,
    INT32_ARRAY_PARAM_TYPE  = 9,
    INT64_ARRAY_PARAM_TYPE  = 10,
    FLT_ARRAY_PARAM_TYPE    = 11,
    DBL_ARRAY_PARAM_TYPE    = 12,
    STRING_PARAM_TYPE       = 13



class PROFILE_DATA_TYPES(IntEnum):
    PIXELS				= 0x10,
    PROFILE				= 0x11,
    PIXELS_INTRP		= 0x12,
    PROFILE_INTRP		= 0x13






_search_mutex = Lock()

_connect_mutex = Lock()



_param_mutex = Lock()

_profile_mutex = Lock()

_buffer_frame_tmp=(c_char*4096*4096*sizeof(c_char))() #buffer for frame

_buffer_profile_tmp = (c_char*8000*max(sizeof(rf627_smart_profile2D_t), sizeof(rf627_old_point2D_t)))() 



CONST_pvtKey=[

    "unkn_t",

    "uint32_t",

    "uint64_t",

    "int32_t",

    "int64_t",

    "float_t",

    "double_t",

    "u32_arr_t",

    "u64_arr_t",

    "i32_arr_t",

    "i64_arr_t",

    "flt_array_t",

    "dbl_array_t",

    "string_t"

    ]



class CONST_paramValueType_t(IntEnum):

        PVT_UNKN        =0

        PVT_UINT        =1

        PVT_UINT64      =2

        PVT_INT =3

        PVT_INT64       =4

        PVT_FLOAT       =5

        PVT_DOUBLE      =6

        PVT_ARRAY_UINT32        =7

        PVT_ARRAY_UINT64        =8

        PVT_ARRAY_INT32 =9

        PVT_ARRAY_INT64 =10

        PVT_ARRAY_FLT   =11

        PVT_ARRAY_DBL   =12

        PVT_STRING      =13



def get_base_by_type(p, type):

    struct_type=None

    base=None

    arr_el_type=None



    #   "unkn_t",

    # "uint32_t",

    if (type==CONST_pvtKey[CONST_paramValueType_t.PVT_UINT]):

        struct_type=struct_value_uint32_t

        base=p.contents.val_uint32



    # "uint64_t",

    elif  (type==CONST_pvtKey[CONST_paramValueType_t.PVT_UINT64]):

        struct_type=struct_value_uint64_t

        base=p.contents.val_uint64

    # "int32_t",

    elif (type==CONST_pvtKey[CONST_paramValueType_t.PVT_INT]):

        struct_type=struct_value_int32_t

        base=p.contents.val_int32

    # "int64_t",

    elif (type==CONST_pvtKey[CONST_paramValueType_t.PVT_INT64]):

        struct_type=struct_value_int64_t

        base=p.contents.val_int64

    # "float_t",

    elif (type==CONST_pvtKey[CONST_paramValueType_t.PVT_FLOAT]):

        struct_type=struct_value_flt_t

        base=p.contents.val_flt

    # "double_t",

    elif (type==CONST_pvtKey[CONST_paramValueType_t.PVT_FLOAT]):

        struct_type=struct_value_flt_t

        base=p.contents.val_flt

    # "u32_arr_t",

    elif (type==CONST_pvtKey[CONST_paramValueType_t.PVT_ARRAY_UINT32]):

        struct_type=struct_array_uint32_t

        base=p.contents.arr_uint32

        arr_el_type=c_uint32

    # "u64_arr_t",

    elif (type==CONST_pvtKey[CONST_paramValueType_t.PVT_ARRAY_UINT64]):

        struct_type=struct_array_uint64_t

        base=p.contents.arr_uint64

        arr_el_type=c_uint64

    # "i32_arr_t",

    elif (type==CONST_pvtKey[CONST_paramValueType_t.PVT_ARRAY_INT32]):

        struct_type=struct_array_int32_t

        base=p.contents.arr_int32

        arr_el_type=c_int32

    # "i64_arr_t",

    elif (type==CONST_pvtKey[CONST_paramValueType_t.PVT_ARRAY_INT64]):

        struct_type=struct_array_int64_t

        base=p.contents.arr_int64

        arr_el_type=c_int64

    # "flt_array_t",

    elif (type==CONST_pvtKey[CONST_paramValueType_t.PVT_ARRAY_FLT]):

        struct_type=struct_array_flt_t

        base=p.contents.arr_flt

        arr_el_type=c_float

    # "dbl_array_t",

    elif (type==CONST_pvtKey[CONST_paramValueType_t.PVT_ARRAY_DBL]):

        struct_type=struct_array_dbl_t

        base=p.contents.arr_dbl

        arr_el_type=c_double

    # "string_t"

    elif (type==CONST_pvtKey[CONST_paramValueType_t.PVT_STRING]):

         struct_type=struct_value_str_t

         base=p.contents.val_str 



    if struct_type:

        return struct_type, base, arr_el_type

    else:

        return None, None, None



def py_get_parameter(p, dummy1, dummy2):

    if p:

        ret=getdict(p.contents.base)

        struct_type, base,arr_el_type=get_base_by_type(p, ret['type'])

        if struct_type:

            base=base.contents

            ret.update(getdict(base))   #the rest of rest keys-values

            ret['ctypes']= (c_char *  sizeof(parameter_t) )()

            memmove(ret['ctypes'], p, sizeof(parameter_t)) #copy ctypes object 

            ret['ctypes']=cast(ret['ctypes'], POINTER(parameter_t))



            ret["struct_type"]=struct_type

            

            #parse value

            if ('_arr_' in ret['type']): #arrays

                val= ret['value']

                val= cast(val, POINTER(ret['count']*arr_el_type)).contents 

                ret['value']=[val[i] for i in range(len(val))]

            #parse default values of ctypes array

            for key, value in ret.items():

                if ('ctypes.' in str(value)):

                    val= cast(value, POINTER(ret['defCount']*arr_el_type)).contents 

                    ret[key]=[val[i] for i in range(len(val))]

            # enumValues

            if 'enumValues' in ret:

                if ret['enumValues']:

                    ret['recCount'] =ret['enumValues'].contents.recCount 

                    labels={}

                    indexes={}

                    keys={}



                    for i in range(ret['recCount']):

                        data=ret['enumValues'].contents.rec[i]

                        key=data.key.decode('utf-8')

                        label=data.label.decode('utf-8')

                        value=data.value

                        keys[key]=i

                        indexes[i]=key

                        labels[key]=label



                    

                    ret['enumKeys']=keys

                    ret['enumIndexes']=indexes

                    ret['enumLabels']=labels



                else:

                    ret['enumKeys']=None

                    ret['enumIndexes']=None

                    ret['enumLabels']=None



            

            return ret



    return None



def parse_py_get_info_about_scanner(p, func, args):

    ret={}

    scannertype=p.scanner_type

    if scannertype==kRF627_OLD:

        ret=getdict(p.rf627old.hello_info_service_protocol.contents)

    elif scannertype==kRF627_SMART:

        ret=getdict(p.rf627smart.hello_info_service_protocol.contents)

    else:

        return None

    

    ret['scanner_type']=p.scanner_type

    ret['protocol_type']=p.protocol_type

    ret['firmware_version']='.'.join(str(x) for x in ret['fact_general_firmwareVer'])

    ret['hardware_version']=parse_version(ret['fact_general_hardwareVer'])

    return ret



# lib.get_profile2D_from_scanner.errcheck = py_get_profile2D_from_scanner

lib.get_parameter.errcheck = py_get_parameter

lib.get_info_about_scanner.errcheck = parse_py_get_info_about_scanner



######################################

# helper functions



def inet_addr(addr):

    return unpack("!I", inet_aton(addr))[0]



def num_to_ip(num):

    return '.'.join(str(x) for x in num)



def num_to_mac(num):

    return ':'.join(format(x, '02x') for x in num)    



def parse_version(version_as_int32):

    num = version_as_int32

    major = (num >> (8 * 3)) & 0xFF

    minor = (num >> (8 * 2)) & 0xFF

    patch = (num >> (8 * 1)) & 0xFF

    return str(major)+"."+str(minor)+"."+str(patch)



def getdict(struct):

    ''' struct to dict'''

    ret={}

    for field, type in struct._fields_:

        ret [field]= getattr(struct, field)

        if ("_Array_") in str(type):

            val= ret [field]

            ret [field]=[val[i] for i in range(len(val))]

        elif ("c_char_p") in str(type):

            ret[field]=ret[field].decode('utf-8')

        elif ("String") in str(type):

            ret[field]=ret[field].data.decode('utf-8')

    return ret 





def sdk_init():

    lib.core_init()



def sdk_cleanup():

    lib.FreeAdapterAddresses()

    if platform.system()=='Windows':

        lib.WinSockDeinit()

def sdk_version():

    return lib.sdk_version()



def read_params(scanner, protocol=kSERVICE, timeout=3000):

    result=False

    _param_mutex.acquire()

    is_connected=lib.check_connection_to_scanner(scanner, timeout,protocol)

    if is_connected:

        result = lib.read_params_from_scanner(scanner, timeout, protocol)

    _param_mutex.release()

    return result



def write_params(scanner, protocol=kSERVICE, timeout=3000):

    result=False

    _param_mutex.acquire()

    result = lib.write_params_to_scanner(scanner, timeout, protocol)

    _param_mutex.release()

    return result



def save_params(scanner, protocol=kSERVICE, timeout=3000):

    result=False

    _param_mutex.acquire()

    result = lib.save_params_to_scanner(scanner, timeout, protocol)

    _param_mutex.release()

    return result



def get_param(scanner, parameter_str_or_int):

    result=None

    _param_mutex.acquire()

    result = lib.get_parameter(scanner, parameter_str_or_int.encode('utf-8'))

    _param_mutex.release()

    return result





def set_param(scanner, p, new_value=None):

    

    result=False

   

    if new_value is not None:

        # read structure into temp_param and update its value

        p =get_param(scanner, p)

        #if enum -- get new value index by key

        if  p["enumKeys"] is not None:

            if new_value in p["enumKeys"]:

                new_value=p["enumKeys"][new_value]

            else:

                #nothing to change

                return False

        p["value"]=new_value



        # changing value and update p structure into temp_param



    temp_param= lib.create_parameter_from_type(p['ctypes'].contents.base.type)

    type=p['type']



    if temp_param:

        name_param=p['ctypes'].contents.base.name

        name_param_size=len(name_param)+1

        temp_param.contents.base.name = c_char_p(name_param)

        temp_param.contents.base.size=name_param_size



        name_param=p['ctypes'].contents.base.access

        name_param_size=len(name_param)+1

        temp_param.contents.base.access = c_char_p(name_param)



        name_param=p['ctypes'].contents.base.units

        name_param_size=len(name_param)+1

        temp_param.contents.base.units = c_char_p(name_param)



        name_param=p['ctypes'].contents.base.type

        name_param_size=len(name_param)+1

        temp_param.contents.base.type = c_char_p(name_param)



        temp_param.contents.base.index= p['ctypes'].contents.base.index

        temp_param.contents.base.offset= p['ctypes'].contents.base.offset

    if "string" in type:

        temp_param.contents.val_str.contents.value= c_char_p(p['value'].encode("utf-8"))

    elif ('arr_' in type): #arrays

        struct_type, _,arr_el_type=get_base_by_type(cast(p['ctypes'], POINTER(parameter_t))  , type)



        newval=(arr_el_type* len(p['value']) )(*p['value'])

        if struct_type==struct_array_uint32_t:

            temp_param.contents.arr_uint32.contents.value=newval

        elif struct_type==struct_array_uint64_t:

            temp_param.contents.arr_uint64.contents.value=newval

        elif struct_type==struct_array_int32_t:

            temp_param.contents.arr_int32.contents.value=newval

        elif struct_type==struct_array_int64_t:

            temp_param.contents.arr_int64.contents.value=newval

        elif struct_type==struct_array_flt_t:

            temp_param.contents.arr_flt.contents.value=newval

        p['size']=sizeof(arr_el_type) * len(p['value'])

        temp_param.contents.base.size=p['size']

    else:

        #numbers

        newval=p['value']

        if type=="uint32_t":

            temp_param.contents.val_uint32.contents.value=newval

        elif type=="uint64_t":

            temp_param.contents.val_uint64.contents.value=newval

        elif type=="int32_t":

            temp_param.contents.val_int32.contents.value=newval

        elif type=="int64_t":

            temp_param.contents.val_int64.contents.value=newval

        elif type=="float_t":

            temp_param.contents.val_flt.contents.value=newval

        elif type=="double_t":

            temp_param.contents.val_dbl.contents.value=newval



    _param_mutex.acquire()

    lib.set_parameter(scanner, temp_param)

    _param_mutex.release()

    lib.platform_free(temp_param)



    return result





def connect(scanner, protocol=kSERVICE):

    _connect_mutex.acquire()

    result = lib.connect_to_scanner(scanner, kSERVICE)

    if result:

        read_params(scanner,protocol)

    _connect_mutex.release()

    return result



def disconnect(scanner,protocol=kSERVICE):

    return lib.disconnect_from_scanner(scanner,protocol)



_scanners=vector_t() #global variable to store list of scanner. need to be in memory all the time



# Initialization vector

def search(timeout=500, protocol=kSERVICE):

    _search_mutex.acquire()



    # Cleaning detected network adapter.

    lib.FreeAdapterAddresses()

    # Retrieving addresses associated with adapters on the local computer.

    lib.EnumAdapterAddresses()

    # Create value for scanners vector's type

    # lib.vector_init(byref(_scanners))

    while lib.vector_count(_scanners)>0:

        lib.vector_delete(_scanners, lib.vector_count(_scanners)-1)

    lib.vector_init(byref(_scanners))

    #  Iterate over all available network adapters in the current operating

    #  system to send "Hello" requests.

    count = 0

    for i in range(lib.GetAdaptersCount()):

        # get another IP Addr and set this changes in network adapter settings.

        host_ip_addr_txt=lib.GetAdapterAddress(i).decode("utf-8")

        host_mask_txt= lib.GetAdapterMasks(i).decode("utf-8")



        host_ip_addr = inet_addr(host_ip_addr_txt)

        host_mask= inet_addr(host_mask_txt)

        # call the function to change adapter settings inside the library.

        lib.set_platform_adapter_settings(host_mask, host_ip_addr)

        #  Search for RF627-Smart devices over network by Service Protocol.

        lib.search_scanners(_scanners, kRF627_SMART, timeout, protocol)

        if (host_ip_addr != 0):

            print("Search scanners from:\n "

            "* IP Address\t: ",host_ip_addr_txt,"\n "

            "* Netmask\t: ",host_mask_txt)

            print("Discovered: ",lib.vector_count(_scanners)-count," RF627-Smart");

            print("-----------------------------------------")

        count = lib.vector_count(_scanners)

    result=[]

    for i in range(lib.vector_count(_scanners)):

        scanner = lib.vector_get(_scanners,i)

        scanner = cast(scanner, POINTER(scanner_base_t))

        result.append(scanner)

    # lib.vector_free(scanners)

    _search_mutex.release()



    return result



def get_info(scanner, protocol=kSERVICE):

    return lib.get_info_about_scanner(scanner, protocol)





def start_dump_recording(scanner, count_of_profiles=1000):

    # Get parameter of user_dump_capacity

    capacity = get_param(scanner,"user_dump_capacity")

    if (capacity is not None and capacity["type"]=="uint32_t"):

        capacity["value"]=count_of_profiles

        set_param(scanner, capacity)

    else:

        return False

    # Get parameter of user_dump_enabled

    enabled  = get_param(scanner,"user_dump_enabled")

    if (enabled is not None and enabled["type"]=="uint32_t"):

        enabled["value"]=True

        set_param(scanner, enabled)

    else:

        return False

    return write_params(scanner)





def py_frame2python(frame_sdk):

    ret={}

    if frame_sdk is not None:

        scanner_type=frame_sdk.contents.type

        if scanner_type==kRF627_OLD:

            frame=frame_sdk.contents.rf627old_frame.contents

            format=rf627_old_frame_t

        elif scanner_type==kRF627_SMART:

            frame=frame_sdk.contents.rf627smart_frame.contents

            format=rf627_smart_frame_t

    ret = getdict(frame)

    #data

    # ret['header']['data']

    if frame.data_size>0:

        c=frame.data_size

        v=frame.data

        

        if memmove(_buffer_frame_tmp, v, c*sizeof(c_char)):

            raw=(c*c_char).from_buffer_copy(_buffer_frame_tmp)

            ret['data']=bytearray(raw.raw)

        else:

            ret.pop('data', None)



    #freemem

    if scanner_type==kRF627_OLD:

        lib.platform_free(frame_sdk.contents.rf627old_frame)  # free ctypes object

    elif scanner_type==kRF627_SMART:

        lib.platform_free(frame_sdk.contents.rf627old_frame)  # free ctypes object

    lib.platform_free(frame_sdk)#free ctypes object 



    return ret





def py_profile2python(profile_sdk):

    ret={}

    if profile_sdk is not None:

        scanner_type=profile_sdk.contents.type

        if scanner_type==kRF627_OLD:

            profile=profile_sdk.contents.rf627old_profile2D.contents

            format=rf627_old_point2D_t

        elif scanner_type==kRF627_SMART:

            profile=profile_sdk.contents.rf627smart_profile2D.contents

            format=rf627_smart_profile2D_t

        ret['header'] = getdict(profile.header)

        datatype = ret['header']['data_type']

        if (datatype == DTY_PixelsNormal) or (datatype == DTY_PixelsInterpolated):

            # pixels_format

            c=profile.pixels_format.pixels_count

            v=profile.pixels_format.pixels

            if memmove(_buffer_profile_tmp, v, c*sizeof(rfUint16)): #copy ctypes object to buffer

                ret['pixels']=(c*rfUint16).from_buffer_copy(_buffer_profile_tmp)

                ret['pixels_count']=c

            lib.platform_free(v) #free ctypes object 

            

        if (datatype == DTY_ProfileNormal) or (datatype == DTY_ProfileInterpolated):

            # profile_format

            c = profile.profile_format.points_count

            v = profile.profile_format.points

            if memmove(_buffer_profile_tmp, v, c*sizeof(rf627_old_point2D_t)):

                ret['points']=(c*rf627_old_point2D_t).from_buffer_copy(_buffer_profile_tmp)

                ret['points_count']=c

            lib.platform_free(v)#free ctypes object 



        if (profile.intensity_count>0):

            #intensity

            c=profile.intensity_count

            v=profile.intensity

            if memmove(_buffer_profile_tmp, v, c*sizeof(rfUint8)):

                ret['intensity']=(c*rfUint8).from_buffer_copy(_buffer_profile_tmp)

                ret['intensity_count']=c

            lib.platform_free(v)#free ctypes object 

            

    

        #freemem

        if scanner_type==kRF627_OLD:

            lib.platform_free(profile_sdk.contents.rf627old_profile2D)  # free ctypes object

        elif scanner_type==kRF627_SMART:

            lib.platform_free(profile_sdk.contents.rf627smart_profile2D)  # free ctypes object

        lib.platform_free(profile_sdk)#free ctypes object 



    return ret



def get_dumps_profiles(scanner, index, count, protocol=kSERVICE):

    result=[]

    fact_dump_unitSize = get_param(scanner, "fact_dump_unitSize")

    if (fact_dump_unitSize is not None and fact_dump_unitSize["type"]=="uint32_t"):

        dumps= (count*POINTER(rf627_profile2D_t))()

        dump_size_val=c_uint32(0)

        unit_size=fact_dump_unitSize["value"]

        status = lib.get_dumps_profiles_from_scanner(

                    scanner, index, count,

                    1000, kSERVICE,

                    (dumps),byref(dump_size_val),

                    unit_size)

        if status:

            dump_size=dump_size_val.value

            for i in range(dump_size):

                result.append(py_profile2python(dumps[i]))

    return result



def get_frame(scanner, protocol=kSERVICE):

    # Establish connection to the RF627 device by Service Protocol.

    _frame = lib.get_frame_from_scanner(scanner, protocol)

    if _frame is not None:

        frame=py_frame2python(_frame)

        frame["width"]=get_param(scanner, "fact_sensor_width")['value']

        frame["height"]=get_param(scanner, "fact_sensor_height")['value']

        frame["pixel_size"]=1 #

        return frame

    else:

        return None



def get_profile2D(scanner, zero_points=True, realtime=True,  protocol=kSERVICE):

    prof=None

    _profile_mutex.acquire()

    is_connected=lib.check_connection_to_scanner(scanner, 3000,protocol)

    if is_connected:

        if protocol==kSERVICE:

            prof = lib.get_profile2D_from_scanner(scanner, zero_points, realtime, kSERVICE)

            prof=py_profile2python(prof)



    _profile_mutex.release()

    return prof



