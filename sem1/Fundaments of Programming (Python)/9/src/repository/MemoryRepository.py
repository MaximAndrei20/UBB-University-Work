from src.repository.Repository_Exception import RepositoryException

class MemoryRepository(object):
    def __init__(self):
        self._objects = []

    def store(self, obj):
        if self.find(obj.id) is not None:
            raise RepositoryException(f"Element having ID {obj.id} already exists")
        self._objects.append(obj)

    def update(self, object):
        """
        Update the instance given as parameter. The provided instance replaces the one having the same ID
        object - The object that will be updated
        Raises RepositoryException in case the object is not contained within the repository
        """
        el = self.find(object.id)
        if el is None:
            raise RepositoryException("Element not found!")
        idx = self._objects.index(el)
        self._objects.remove(el)
        self._objects.insert(idx, object)

    def find(self, object_id):
        for e in self._objects:
            if object_id == e.id:
                return e
        return None

    def delete(self, objectId):
        """
        Remove the object with given objectId from repository
        objectId - The objectId that will be removed
        Returns the object that was removed
        Raises RepositoryException if object with given objectId is not contained in the repository
        """
        object = self.find(objectId)
        if object is None:
            raise RepositoryException("Element not in repository!")
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
