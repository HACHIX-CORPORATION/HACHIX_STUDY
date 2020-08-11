from abc import ABC, abstractmethod


class Camera(ABC):

    @abstractmethod
    def _open(self):
        pass

    @abstractmethod
    def _close(self):
        pass

    @abstractmethod
    def _capture(self):
        return f"capturing image .."

    def capture_once(self):
        self._open()

        self._image = self._capture()

        self._close()

        return self._image


class RGBCamera(Camera):

    def __init__(self):
        pass

    def _open(self):
        print("rgb camera open")

    def _capture(self):
        print("rgb camera capture")

    def _close(self):
        print("rgb camera close")


class DepthCamera(Camera):

    def __init__(self):
        pass

    def _open(self):
        print("depth camera open")

    def _capture(self):
        print("depth camera capture")

    def _close(self):
        print("depth camera close")


class Image(ABC):

    @abstractmethod
    def get_binary(self):
        pass


class DepthImage(Image):

    def __init__(self, width, height):
        self.__width = width
        self.__height = height
        print("This image has shape of ({}, {})".format(width, height))

    def get_binary(self):
        print("get binary of depth image")


class RGBImage(Image):

    def __init__(self, width, height):
        self.__width = width
        self.__height = height
        print("This image has shape of ({}, {})".format(width, height))

    def get_binary(self):
        print("get binary of rgb image")


if __name__ == "__main__":
    rgb_camera = RGBCamera()

    rgb_image = rgb_camera.capture_once()

    print(rgb_image)

    depth_camera = DepthCamera()

    depth_image = depth_camera.capture_once()

    print(depth_image)
