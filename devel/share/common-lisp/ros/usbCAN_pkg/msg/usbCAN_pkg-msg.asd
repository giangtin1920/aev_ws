
(cl:in-package :asdf)

(defsystem "usbCAN_pkg-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "CAN_msg" :depends-on ("_package_CAN_msg"))
    (:file "_package_CAN_msg" :depends-on ("_package"))
  ))