import fileupload

def _upload():

    _upload_widget = fileupload.FileUploadWidget()

    def _cb(change):
        decoded = io.StringIO(change['owner'].data.decode('utf-8'))
        filename = change['owner'].filename
        print('Uploaded `{}` ({:.2f} kB)'.format(
            filename, len(decoded.read()) / 2 **10))

    _upload_widget.observe(_cb, names='data')
    display(_upload_widget)

_upload()