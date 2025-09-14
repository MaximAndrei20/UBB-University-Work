class Repository:
    def __init__(self):
        self._objects = []

    def add(self, obj):
        if self.find(obj.id) is not None:
            raise Exception("Element having id=" + str(obj.id) + " already stored!")
        self._objects.append(obj)

    def update(self, object):
        el = self.find(object.id)
        if el is None:
            raise Exception("Element not found!")
        idx = self._objects.index(el)
        self._objects.remove(el)
        self._objects.insert(idx, object)

    def find(self, objectId):
        for e in self._objects:
            if objectId == e.id:
                return e
        return None

    def delete(self, objectId):
        object = self.find(objectId)
        if object is None:
            raise Exception("Element not in repository!")
        self._objects.remove(object)
        return object

    def get_all(self):
        return self._objects

    def __len__(self):
        return len(self._objects)

    def __str__(self):
        r = ""
        for e in self._objects:
            r += str(e)
            r += "\n"
        return r