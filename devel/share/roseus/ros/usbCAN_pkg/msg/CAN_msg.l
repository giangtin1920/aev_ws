;; Auto-generated. Do not edit!


(when (boundp 'usbcan_pkg::can_msg)
  (if (not (find-package "USBCAN_PKG"))
    (make-package "USBCAN_PKG"))
  (shadow 'can_msg (find-package "USBCAN_PKG")))
(unless (find-package "USBCAN_PKG::CAN_MSG")
  (make-package "USBCAN_PKG::CAN_MSG"))

(in-package "ROS")
;;//! \htmlinclude can_msg.msg.html


(defclass usbcan_pkg::can_msg
  :super ros::object
  :slots (_id _type _length _data ))

(defmethod usbcan_pkg::can_msg
  (:init
   (&key
    ((:id __id) 0)
    ((:type __type) 0)
    ((:length __length) 0)
    ((:data __data) (make-array 8 :initial-element 0 :element-type :char))
    )
   (send-super :init)
   (setq _id (round __id))
   (setq _type (round __type))
   (setq _length (round __length))
   (setq _data __data)
   self)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:type
   (&optional __type)
   (if __type (setq _type __type)) _type)
  (:length
   (&optional __length)
   (if __length (setq _length __length)) _length)
  (:data
   (&optional __data)
   (if __data (setq _data __data)) _data)
  (:serialization-length
   ()
   (+
    ;; uint32 _id
    4
    ;; uint8 _type
    1
    ;; uint8 _length
    1
    ;; uint8[8] _data
    (* 1    8)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint32 _id
       (write-long _id s)
     ;; uint8 _type
       (write-byte _type s)
     ;; uint8 _length
       (write-byte _length s)
     ;; uint8[8] _data
     (princ _data s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint32 _id
     (setq _id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint8 _type
     (setq _type (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _length
     (setq _length (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8[8] _data
   (setq _data (make-array 8 :element-type :char))
   (replace _data buf :start2 ptr-) (incf ptr- 8)
   ;;
   self)
  )

(setf (get usbcan_pkg::can_msg :md5sum-) "92ef1a7d09d3119fcbbcfe293f3fd075")
(setf (get usbcan_pkg::can_msg :datatype-) "usbcan_pkg/can_msg")
(setf (get usbcan_pkg::can_msg :definition-)
      "uint32 id
uint8 type
uint8 length
uint8[8] data


")



(provide :usbcan_pkg/can_msg "92ef1a7d09d3119fcbbcfe293f3fd075")


