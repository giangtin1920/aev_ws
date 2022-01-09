
(cl:in-package :asdf)

(defsystem "usbcan_pkg-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "can_msg" :depends-on ("_package_can_msg"))
    (:file "_package_can_msg" :depends-on ("_package"))
  ))