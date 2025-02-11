class Solution:
    def maxPathSum(self, root) -> int:
        self.res = float('-inf')
        self.dfs(root)
        return self.res

    def dfs(self, root):
        if root is None:
            return 0

        left = max(0,(self.dfs(root.left))) # Levo ou não ?
        right = max(0, ( self.dfs(root.right))) # Levo ou não ?

        sum = root.val + left + right
        self.res = sum if sum > self.res else self.res
        return root.val + max(left, right)
