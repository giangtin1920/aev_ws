;; Auto-generated. Do not edit!


(when (boundp 'aev_pkg::radar_msg)
  (if (not (find-package "AEV_PKG"))
    (make-package "AEV_PKG"))
  (shadow 'radar_msg (find-package "AEV_PKG")))
(unless (find-package "AEV_PKG::RADAR_MSG")
  (make-package "AEV_PKG::RADAR_MSG"))

(in-package "ROS")
;;//! \htmlinclude radar_msg.msg.html


(defclass aev_pkg::radar_msg
  :super ros::object
  :slots (_msg_counter _isObject _distance ))

(defmethod aev_pkg::radar_msg
  (:init
   (&key
    ((:msg_counter __msg_counter) 0)
    ((:isObject __isObject) nil)
    ((:distance __distance) 0.0)
    )
   (send-super :init)
   (setq _msg_counter (round __msg_counter))
   (setq _isObject __isObject)
   (setq _distance (float __distance))
   self)
  (:msg_counter
   (&optional __msg_counter)
   (if __msg_counter (setq _msg_counter __msg_counter)) _msg_counter)
  (:isObject
   (&optional __isObject)
   (if __isObject (setq _isObject __isObject)) _isObject)
  (:distance
   (&optional __distance)
   (if __distance (setq _distance __distance)) _distance)
  (:serialization-length
   ()
   (+
    ;; uint32 _msg_counter
    4
    ;; bool _isObject
    1
    ;; float32 _distance
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint32 _msg_counter
       (write-long _msg_counter s)
     ;; bool _isObject
       (if _isObject (write-byte -1 s) (write-byte 0 s))
     ;; float32 _distance
       (sys::poke _distance (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint32 _msg_counter
     (setq _msg_counter (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; bool _isObject
     (setq _isObject (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; float32 _distance
     (setq _distance (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get aev_pkg::radar_msg :md5sum-) "cbc61f5430d101edd8000fb728a64c35")
(setf (get aev_pkg::radar_msg :datatype-) "aev_pkg/radar_msg")
(setf (get aev_pkg::radar_msg :definition-)
      "uint32 msg_counter
bool isObject
float32 distance

")



(provide :aev_pkg/radar_msg "cbc61f5430d101edd8000fb728a64c35")


