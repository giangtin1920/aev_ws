; Auto-generated. Do not edit!


(cl:in-package usbCAN_pkg-msg)


;//! \htmlinclude CAN_msg.msg.html

(cl:defclass <CAN_msg> (roslisp-msg-protocol:ros-message)
  ((id
    :reader id
    :initarg :id
    :type cl:integer
    :initform 0)
   (type
    :reader type
    :initarg :type
    :type cl:fixnum
    :initform 0)
   (length
    :reader length
    :initarg :length
    :type cl:fixnum
    :initform 0)
   (data
    :reader data
    :initarg :data
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 8 :element-type 'cl:fixnum :initial-element 0)))
)

(cl:defclass CAN_msg (<CAN_msg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CAN_msg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CAN_msg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name usbCAN_pkg-msg:<CAN_msg> is deprecated: use usbCAN_pkg-msg:CAN_msg instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <CAN_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader usbCAN_pkg-msg:id-val is deprecated.  Use usbCAN_pkg-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'type-val :lambda-list '(m))
(cl:defmethod type-val ((m <CAN_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader usbCAN_pkg-msg:type-val is deprecated.  Use usbCAN_pkg-msg:type instead.")
  (type m))

(cl:ensure-generic-function 'length-val :lambda-list '(m))
(cl:defmethod length-val ((m <CAN_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader usbCAN_pkg-msg:length-val is deprecated.  Use usbCAN_pkg-msg:length instead.")
  (length m))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <CAN_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader usbCAN_pkg-msg:data-val is deprecated.  Use usbCAN_pkg-msg:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CAN_msg>) ostream)
  "Serializes a message object of type '<CAN_msg>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'type)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'length)) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream))
   (cl:slot-value msg 'data))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CAN_msg>) istream)
  "Deserializes a message object of type '<CAN_msg>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'type)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'length)) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'data) (cl:make-array 8))
  (cl:let ((vals (cl:slot-value msg 'data)))
    (cl:dotimes (i 8)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:aref vals i)) (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CAN_msg>)))
  "Returns string type for a message object of type '<CAN_msg>"
  "usbCAN_pkg/CAN_msg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CAN_msg)))
  "Returns string type for a message object of type 'CAN_msg"
  "usbCAN_pkg/CAN_msg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CAN_msg>)))
  "Returns md5sum for a message object of type '<CAN_msg>"
  "92ef1a7d09d3119fcbbcfe293f3fd075")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CAN_msg)))
  "Returns md5sum for a message object of type 'CAN_msg"
  "92ef1a7d09d3119fcbbcfe293f3fd075")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CAN_msg>)))
  "Returns full string definition for message of type '<CAN_msg>"
  (cl:format cl:nil "uint32 id~%uint8 type~%uint8 length~%uint8[8] data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CAN_msg)))
  "Returns full string definition for message of type 'CAN_msg"
  (cl:format cl:nil "uint32 id~%uint8 type~%uint8 length~%uint8[8] data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CAN_msg>))
  (cl:+ 0
     4
     1
     1
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'data) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CAN_msg>))
  "Converts a ROS message object to a list"
  (cl:list 'CAN_msg
    (cl:cons ':id (id msg))
    (cl:cons ':type (type msg))
    (cl:cons ':length (length msg))
    (cl:cons ':data (data msg))
))
