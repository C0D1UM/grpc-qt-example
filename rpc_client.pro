QT += concurrent widgets

DEFINES += QT_DEPRECATED_WARNINGS

QMAKE_CXXFLAGS += -std=c++17

INCLUDEPATH += $$PWD/vcpkg/include

SRCDIR = "rpc_client_cpp"

SOURCES += \
  $$SRCDIR/hellostream_client.cpp \
  $$SRCDIR/route_guide.grpc.pb.cc \
  $$SRCDIR/route_guide.pb.cc \
  $$SRCDIR/chat_client_gui.cpp \
  $$SRCDIR/route_guide_client.cpp \

HEADERS += \
  $$SRCDIR/route_guide.grpc.pb.h \
  $$SRCDIR/route_guide.pb.h \
  $$SRCDIR/chat_client_gui.h \
  $$SRCDIR/route_guide_client.h \

macx {
  debug {
    PRE_TARGETDEPS += \
      $$PWD/vcpkg/debug/lib/libgrpc++.a
      $$PWD/vcpkg/debug/lib/libgrpc.a
      $$PWD/vcpkg/debug/lib/libgpr.a
      $$PWD/vcpkg/debug/lib/libcrypto.a
      $$PWD/vcpkg/debug/lib/libssl.a
      $$PWD/vcpkg/debug/lib/libz.a
      $$PWD/vcpkg/debug/lib/libcares.a
      $$PWD/vcpkg/debug/lib/libprotobufd.a

    LIBS += -L$$PWD/vcpkg/debug/lib/ -lgrpc++ -lgrpc -lgpr -lcrypto -lssl -lz -lcares -lprotobufd
  }

  release {
    PRE_TARGETDEPS += \
      $$PWD/vcpkg/lib/libgrpc++.a
      $$PWD/vcpkg/lib/libgrpc.a
      $$PWD/vcpkg/lib/libgpr.a
      $$PWD/vcpkg/lib/libcrypto.a
      $$PWD/vcpkg/lib/libssl.a
      $$PWD/vcpkg/lib/libz.a
      $$PWD/vcpkg/lib/libcares.a
      $$PWD/vcpkg/lib/libprotobufd.a

    LIBS += -L$$PWD/vcpkg/lib/ -lgrpc++ -lgrpc -lgpr -lcrypto -lssl -lz -lcares -lprotobuf
  }
}

