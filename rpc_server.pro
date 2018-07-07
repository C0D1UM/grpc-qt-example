QT -= gui
QT += concurrent

CONFIG += console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

QMAKE_CXXFLAGS += -std=c++17

INCLUDEPATH += $$PWD/vcpkg/include

SRCDIR = "rpc_server"

SOURCES += \
  $$SRCDIR/main.cpp \
  $$SRCDIR/helloworld.pb.cc \
  $$SRCDIR/helloworld.grpc.pb.cc \
  $$SRCDIR/hellostream.pb.cc \
  $$SRCDIR/hellostream.grpc.pb.cc \
  $$SRCDIR/hellostream_server.cpp \
  $$SRCDIR/route_guide.grpc.pb.cc \
  $$SRCDIR/route_guide.pb.cc \

HEADERS += \
  $$SRCDIR/helloworld_server.h \
  $$SRCDIR/helloworld.pb.h \
  $$SRCDIR/helloworld.grpc.pb.h \
  $$SRCDIR/hellostream.pb.h \
  $$SRCDIR/hellostream.grpc.pb.h \
  $$SRCDIR/hellostream_server.h \
  $$SRCDIR/route_guide.grpc.pb.h \
  $$SRCDIR/route_guide.pb.h

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

DISTFILES += \
    route_guide.proto

